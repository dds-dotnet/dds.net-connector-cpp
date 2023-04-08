#include "src/internal/inc/network_client.h"

#include "inc/error.h"
#include "inc/logger.h"

#include "src/internal/inc/macros.h"

#include "src/internal/inc/sync_queue_reader.h"
#include "src/internal/inc/sync_queue_writer.h"
#include "src/internal/inc/sync_queue.h"

#include "src/internal/inc/packet_from_server.h"
#include "src/internal/inc/packet_to_server.h"

#include "src/internal/inc/buffer_manager.h"
#include "src/internal/inc/string_helper.h"

#include <exception>

#include <stdio.h>


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

  this->unableToConnectMessageFlag = false;
  this->isSocketCreated = false;


#if     TARGET_PLATFORM == PLATFORM_GNU_LINUX
  this->socketFileDescriptor = -1;
#elif   TARGET_PLATFORM == PLATFORM_WINDOWS
  this->socketFileDescriptor = INVALID_SOCKET;
#else
  #error "Cannot initialize this->socketFileDescriptor on selected platform"
#endif


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
  net->isConnected = false;

  //- 
  //- The thread functionality
  //- 
  while (net->isIOThreadStarted)
  {
    if (net->isConnected == false)
    {
      net->connectWithServer();

      if (net->isConnected == false)
      {
        sleep_msec(500);
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

        if (net->isDataAvailable())
        {
          doneAnythingInIteration = true;

          BufferAddress bytes = net->bufferManager->get4k();

          int totalReceived = recv(net->socketFileDescriptor, bytes, 4096, 0);

          if (totalReceived <= 0)
          {
            net->isConnected = false;
            net->closeSocket();

            if (net->onDisconnected != nullptr)
            {
              net->onDisconnected(net->onDisconnectedObj);
            }

            net->bufferManager->free(bytes);

            throw std::exception();
          }
          else
          {
            net->dataFromServerQueue->enqueue(new PacketFromServer(bytes, totalReceived));
          }
        }

        //- 
        //- Transmitting data
        //- 

        while (net->dataToServerQueue->canDequeue())
        {
          doneAnythingInIteration = true;

          PacketToServer* packet = net->dataToServerQueue->dequeue();

          send(net->socketFileDescriptor, packet->buffer, packet->size, 0);

          net->bufferManager->free(packet->buffer);
          delete(packet);
        }
      }
      catch (std::exception&)
      {
        net->isConnected = false;
        net->closeSocket();

        if (net->onDisconnected != nullptr)
        {
          net->onDisconnected(net->onDisconnectedObj);
        }
      }

      if (!doneAnythingInIteration)
      {
        sleep_msec(10);
      }
    }
  } // while (isIOThreadStarted)

  net->closeSocket();
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

#if   TARGET_PLATFORM == PLATFORM_WINDOWS

      unsigned long _temp;

      if (inet_pton(AF_INET, this->ipv4.c_str(), &_temp) != 1)
      {
        struct addrinfo* result = NULL, hints;

        ZeroMemory(&hints, sizeof(hints));

        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;

        char _target_port_str[7];

        sprintf_s(_target_port_str, "%d", tcpPort);

        if (getaddrinfo(this->ipv4.c_str(), _target_port_str, &hints, &result) != 0)
        {
          std::string error = "Failed to resolve the hostname: ";
          error += this->ipv4;

          logger->error(error.c_str());
          dataLock.unlock();
          return;
        }

        for (struct addrinfo* ptr = result; ptr != NULL; ptr = ptr->ai_next)
        {
          targetSocketAddress = *((struct sockaddr_in*)ptr->ai_addr);
          break;
        }
      }
      else
      {
        inet_pton(AF_INET, this->ipv4.c_str(), &targetSocketAddress.sin_addr.s_addr);
      }

      targetSocketAddress.sin_family = AF_INET;
      targetSocketAddress.sin_port = htons(tcpPort);

#elif TARGET_PLATFORM == PLATFORM_GNU_LINUX

      if (inet_addr(this->ipv4.c_str()) == INADDR_NONE)
      {
        struct hostent* he;
        struct in_addr** addr_list;

        if ((he = gethostbyname(this->ipv4.c_str())) == NULL)
        {
          std::string error = "Failed to resolve the hostname: ";
          error += this->ipv4;

          logger->error(error.c_str());
          dataLock.unlock();
          return;
        }

        addr_list = (struct in_addr**)he->h_addr_list;

        for (int i = 0; addr_list[i] != NULL; i++)
        {
          targetSocketAddress.sin_addr = *addr_list[i];
          break;
        }
      }
      else
      {
        targetSocketAddress.sin_addr.s_addr = inet_addr(this->ipv4.c_str());
      }

      targetSocketAddress.sin_family = AF_INET;
      targetSocketAddress.sin_port = htons(tcpPort);

#else
      #error "No conversion of IP address defined for selected platform"
#endif
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

bool
  dds::net::connector::_internal::
  NetworkClient::createSocket()
{
  if (isSocketCreated == false)
  {
    socketFileDescriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

#if     TARGET_PLATFORM == PLATFORM_GNU_LINUX
    if (socketFileDescriptor == -1)
#elif   TARGET_PLATFORM == PLATFORM_WINDOWS
    if (socketFileDescriptor == INVALID_SOCKET)
#else
#error "Cannot check socket validity on selected platform"
#endif
    {
      std::string msg = "Socket cannot be created for TCP Client being connected with ";
      msg += ipv4;
      msg += ":";
      msg += std::to_string(tcpPort);

      logger->error(msg.c_str());

      isSocketCreated = false;
    }

    isSocketCreated = true;
  }

  return isSocketCreated;
}

void
  dds::net::connector::_internal::
  NetworkClient::closeSocket()
{
  if (isSocketCreated == true)
  {
    isSocketCreated = false;

#if     TARGET_PLATFORM == PLATFORM_GNU_LINUX
    close(socketFileDescriptor);
#elif   TARGET_PLATFORM == PLATFORM_WINDOWS
    closesocket(socketFileDescriptor);
#else
#error "Cannot close socket on selected platform"
#endif
  }
}

void
  dds::net::connector::_internal::
  NetworkClient::connectWithServer()
{
  if (createSocket())
  {
    int connectionStatus =
      ::connect(socketFileDescriptor,
        (struct sockaddr*)&(targetSocketAddress),
        sizeof(targetSocketAddress));

#if     TARGET_PLATFORM == PLATFORM_GNU_LINUX
    if (connectionStatus < 0)
#elif   TARGET_PLATFORM == PLATFORM_WINDOWS
    if (connectionStatus == SOCKET_ERROR)
#else
    #error "Cannot check socket connection status for selected platform"
#endif
    {
      if (unableToConnectMessageFlag == false)
      {
        unableToConnectMessageFlag = true;

        std::string errorMessage = "Unable to connect to ";
        errorMessage += ipv4;
        errorMessage += ":";
        errorMessage += std::to_string(tcpPort);

        logger->error(errorMessage.c_str());
        closeSocket();
      }
    }
    else
    {
      unableToConnectMessageFlag = false;

#if   TARGET_PLATFORM == PLATFORM_GNU_LINUX
      int status = fcntl(socketFileDescriptor, F_SETFL, fcntl(socketFileDescriptor, F_GETFL, 0) | O_NONBLOCK);

      if (status == -1)
      {
        std::string errorMessage = "Unable to set TCP connection with ";
        errorMessage += ipv4;
        errorMessage += ":";
        errorMessage += std::to_string(tcpPort);
        errorMessage += " as non-blocking";

        logger->warning(errorMessage.c_str());
      }
#elif   TARGET_PLATFORM == PLATFORM_WINDOWS
      u_long mode = 1;
      int nonBlockingModeResult = ioctlsocket(socketFileDescriptor, FIONBIO, &mode);

      if (nonBlockingModeResult == SOCKET_ERROR)
      {
        std::string errorMessage = "Unable to set TCP connection with ";
        errorMessage += ipv4;
        errorMessage += ":";
        errorMessage += std::to_string(tcpPort);
        errorMessage += " as non-blocking";

        logger->warning(errorMessage.c_str());
      }
#else
#error "Cannot set socket to non-blocking for selected platform"
#endif

      dataToServerQueue->clear();
      dataFromServerQueue->clear();

      if (onConnected != nullptr)
      {
        onConnected(onConnectedObj);
      }

      isConnected = true;
    }
  }
}

bool
  dds::net::connector::_internal::
  NetworkClient::isDataAvailable(int timeoutSecond, int timeoutMicrosecond)
{
#if   TARGET_PLATFORM == PLATFORM_GNU_LINUX

  timeval tv;
  fd_set readfds;

  tv.tv_sec = timeoutSecond;
  tv.tv_usec = timeoutMicrosecond;

  FD_ZERO(&readfds);
  FD_SET(socketFileDescriptor, &readfds);

  // don't care about write and exception descriptors
  select(socketFileDescriptor + 1, &readfds, NULL, NULL, &tv);

  if (FD_ISSET(socketFileDescriptor, &readfds))
  {
    return true;
  }
  else
  {
    return false;
  }

#elif TARGET_PLATFORM == PLATFORM_WINDOWS

  timeval tv;
  fd_set readfds;

  tv.tv_sec = timeoutSecond;
  tv.tv_usec = timeoutMicrosecond;

  FD_ZERO(&readfds);
  FD_SET(socketFileDescriptor, &readfds);

  select((int)socketFileDescriptor + 1, &readfds, NULL, NULL, &tv);

  if (FD_ISSET(socketFileDescriptor, &readfds))
  {
    return true;
  }
  else
  {
    return false;
  }

#else
#error "Cannot check packet availability on selected platform"
#endif
}
