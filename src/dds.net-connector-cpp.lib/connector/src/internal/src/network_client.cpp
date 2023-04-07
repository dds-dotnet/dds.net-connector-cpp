#include "src/internal/inc/network_client.h"

#include "inc/error.h"
#include "inc/logger.h"

#include "src/internal/inc/sync_queue_reader.h"
#include "src/internal/inc/sync_queue_writer.h"
#include "src/internal/inc/sync_queue.h"

#include "src/internal/inc/string_helper.h"

#include <exception>


using namespace dds::net::connector;
using namespace dds::net::connector::_internal;



#if   TARGET_PLATFORM == PLATFORM_WINDOWS

static int wsaStartCount = 0;

#endif



dds::net::connector::_internal::
  NetworkClient::NetworkClient(
    Logger* logger,
    BufferManager* bufferManager,
    int dataToServerQueueSize,
    int dataFromServerQueueSize)
{
  this->logger = logger;

  if (this->logger == nullptr)
  {
    this->logger = new BlankLogger();
  }

  this->bufferManager = bufferManager;

  this->onConnected = nullptr;
  this->onConnectedObj = nullptr;

  this->onDisconnected = nullptr;
  this->onDisconnectedObj = nullptr;

  this->dataToServerQueue = new SyncQueue<PacketToServer*>(dataToServerQueueSize);
  this->dataFromServerQueue = new SyncQueue<PacketFromServer*>(dataFromServerQueueSize);

  this->isIOThreadStarted = false;
  this->ioThread = nullptr;

  this->ipv4 = "";
  this->tcpPort = 0;
  this->isConnected = false;
  this->socketFileDescriptor = -1;

  memset(&this->targetSocketAddress, 0, sizeof(this->targetSocketAddress));



#if   TARGET_PLATFORM == PLATFORM_WINDOWS

  if (wsaStartCount == 0)
  {
    WSADATA wsaData;

    int windowsStartupResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (windowsStartupResult != 0)
    {
      std::string msg = "WSAStartup failed with error code: ";
      msg += windowsStartupResult;

      this->logger->error(msg.c_str());
    }
    else
    {
      this->logger->info("WSA Started.");
    }
  }

  wsaStartCount++;

#endif
}

dds::net::connector::_internal::
  NetworkClient::~NetworkClient()
{
#if   TARGET_PLATFORM == PLATFORM_WINDOWS

  wsaStartCount--;

  if (wsaStartCount == 0)
  {
    WSACleanup();
    this->logger->info("WSA Cleaned-up.");
  }

#endif
}

SyncQueueReader<PacketFromServer*>*
  dds::net::connector::_internal::
  NetworkClient::getDataQueueFromServer()
{
    return dataFromServerQueue;
}

SyncQueueWriter<PacketToServer*>*
  dds::net::connector::_internal::
  NetworkClient::getDataQueueToServer()
{
    return dataToServerQueue;
}

void
  dds::net::connector::_internal::
  NetworkClient::setCallbackOnConnectedWithServer(
    connectedCallback callback,
    void* obj)
{
  onConnected = callback;
  onConnectedObj = obj;
}

void
  dds::net::connector::_internal::
  NetworkClient::setCallbackOnDisconnectedFromServer(
    disconnectedCallback callback,
    void* obj)
{
  onDisconnected = callback;
  onDisconnectedObj = obj;
}


void
  dds::net::connector::_internal::
  ioThreadFunc(NetworkClient* net)
{
  while (net->isIOThreadStarted)
  {
    if (net->isConnected == false)
    {
      net->socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);


#if   TARGET_PLATFORM == PLATFORM_GNU_LINUX
      if (net->socketFileDescriptor == -1)
#elif   TARGET_PLATFORM == PLATFORM_WINDOWS
      if (net->socketFileDescriptor == INVALID_SOCKET)
#else
      #error "Cannot check socket validity on selected platform"
#endif
      {
        std::string msg = "Socket cannot be created for TCP Client connecting with ";
        msg += net->ipv4;
        msg += ":";
        msg += net->tcpPort;

        net->logger->error(msg.c_str());

        net->isIOThreadStarted = false;
        return;
      }
      try
      {
        socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp)
        {
            Blocking = false
        };
      }
      catch (Exception)
      {
        try
        {
          socket ? .Close();
          socket ? .Dispose();
        }
        catch { }

        socket = null!;
      }
    }
    else
    {
      if (!socket.Connected)
      {
        try
        {
          socket.ConnectAsync(targetEndPoint);

          dataToServerQueue.Clear();
          dataFromServerQueue.Clear();

          ConnectedWithServer ? .Invoke();
        }
        catch
        {
          Thread.Sleep(100);
        }
      }
      else
      {
        bool doneAnythingInIteration = false;

        try
        {
          //- 
          //- Receiving data
          //- 

          if (socket.Available > 0)
          {
            doneAnythingInIteration = true;

            byte[] bytes = new byte[socket.Available];

            int totalReceived = socket.Receive(bytes, SocketFlags.None);

            dataFromServerQueue.Enqueue(new PacketFromServer(bytes));
          }

          //- 
          //- Transmitting data
          //- 

          while (dataToServerQueue.CanDequeue())
          {
            doneAnythingInIteration = true;

            PacketToServer packet = dataToServerQueue.Dequeue();

            socket.Send(packet.Data, packet.TotalBytesToBeSent, SocketFlags.None);
          }
        }
        catch
        {
          DisconnectedFromServer ? .Invoke();

          try
          {
            socket ? .Close();
            socket ? .Dispose();
          }
          catch { }

          socket = null!;
        }

        if (!doneAnythingInIteration)
        {
          Thread.Sleep(10);
        }
      }
    }
  } // while (isIOThreadStarted)

  if (socket ? .Connected == true)
  {
    try
    {
      DisconnectedFromServer ? .Invoke();
      socket ? .DisconnectAsync(false);
    }
    catch { }
  }


#if   TARGET_PLATFORM == PLATFORM_GNU_LINUX
  if (net->socketFileDescriptor != -1)
  {
    close(socketFileDescriptor);
  }
#elif   TARGET_PLATFORM == PLATFORM_WINDOWS
  closesocket(socketFileDescriptor);
#else
#error "Cannot close socket on selected platform"
#endif
}


void
  dds::net::connector::_internal::
  NetworkClient::connect(
    std::string ipv4,
    unsigned short tcpPort)
{
  dataLock.lock();


  if (isIOThreadStarted)
  {
    dataLock.unlock();
    throw Error("The connection routine has already been started.");
  }
  else
  {
    if (StringHelper::isValidIPv4Address(ipv4))
    {
      this->ipv4 = ipv4;
      this->tcpPort = tcpPort;
    }
    else
    {
      dataLock.unlock();

      std::string msg = "Invalid IPv4 address: ";
      msg += ipv4;

      throw Error(msg.c_str());
    }

    isIOThreadStarted = true;
    ioThread = new std::thread(ioThreadFunc, this);
  }


  dataLock.unlock();
}

void
  dds::net::connector::_internal::
  NetworkClient::disconnect()
{
  dataLock.lock();



  if (isIOThreadStarted)
  {
    try
    {
      isIOThreadStarted = false;

      ioThread->join();
      ioThread = nullptr;
    }
    catch (std::exception&)
    {

    }
  }



  dataLock.unlock();
}
