#include "src/internal/inc/packet_to_server.h"



dds::net::connector::_internal::
  PacketToServer::PacketToServer(BufferAddress buffer, int size)
{
  this->buffer = buffer;
  this->size = size;
}
