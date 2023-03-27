#include "src/internal/inc/network_client.h"

#include "src/internal/inc/sync_queue_reader.h"
#include "src/internal/inc/sync_queue_writer.h"


using namespace dds::net::connector::_internal;


SyncQueueReader<PacketFromServer>* dds::net::connector::_internal::NetworkClient::getDataQueueFromServer()
{
    return nullptr;
}

SyncQueueWriter<PacketToServer>* dds::net::connector::_internal::NetworkClient::getDataQueueToServer()
{
    return nullptr;
}

void dds::net::connector::_internal::NetworkClient::setCallbackOnConnectedWithServer(connectedCallback callback, void* obj)
{
}

void dds::net::connector::_internal::NetworkClient::setCallbackOnDisconnectedFromServer(disconnectedCallback callback, void* obj)
{
}

void dds::net::connector::_internal::NetworkClient::connect(std::string ipv4, unsigned short tcpPort)
{
}

void dds::net::connector::_internal::NetworkClient::disconnect()
{
}
