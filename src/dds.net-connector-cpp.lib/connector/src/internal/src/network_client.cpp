#include "src/internal/inc/network_client.h"

#include "src/internal/inc/sync_queue_reader.h"
#include "src/internal/inc/sync_queue_writer.h"
#include "src/internal/inc/sync_queue.h"


using namespace dds::net::connector::_internal;


dds::net::connector::_internal::
  NetworkClient::NetworkClient(
    BufferManager* bufferManager,
    int dataToServerQueueSize,
    int dataFromServerQueueSize)
{
  this->bufferManager = bufferManager;

  this->onConnected = nullptr;
  this->onConnectedObj = nullptr;

  this->onDisconnected = nullptr;
  this->onDisconnectedObj = nullptr;

  this->dataToServerQueue = new SyncQueue<PacketToServer*>(dataToServerQueueSize);
  this->dataFromServerQueue = new SyncQueue<PacketFromServer*>(dataFromServerQueueSize);
}

SyncQueueReader<PacketFromServer*>*
  dds::net::connector::_internal::
  NetworkClient::getDataQueueFromServer()
{
    return nullptr;
}

SyncQueueWriter<PacketToServer*>*
  dds::net::connector::_internal::
  NetworkClient::getDataQueueToServer()
{
    return nullptr;
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
  NetworkClient::connect(
    std::string ipv4,
    unsigned short tcpPort)
{
}

void
  dds::net::connector::_internal::
  NetworkClient::disconnect()
{
}
