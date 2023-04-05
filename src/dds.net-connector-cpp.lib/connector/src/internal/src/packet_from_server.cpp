#include "src/internal/inc/packet_from_server.h"



dds::net::connector::_internal::
  PacketFromServer::PacketFromServer(BufferAddress buffer, int size)
{
  this->buffer = buffer;
  this->size = size;
}
