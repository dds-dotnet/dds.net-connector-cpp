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
    return;
}
  }

  wsaStartCount++;

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
  ioThreadFunc(NetworkClient* client)
{

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
