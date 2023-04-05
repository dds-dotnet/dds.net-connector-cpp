#include "src/internal/inc/packet_preprocessor.h"

#include "src/internal/inc/buffer_manager.h"
#include "src/internal/inc/packet_from_server.h"

dds::net::connector::_internal::
  PacketPreprocessor::PacketPreprocessor(BufferManager* bufferManager)
{
  this->bufferManager = bufferManager;
}

dds::net::connector::_internal::
  PacketPreprocessor::~PacketPreprocessor()
{
}

void
  dds::net::connector::_internal::
  PacketPreprocessor::addData(PacketFromServer* packet)
{

  delete packet;
}

BufferAddress dds::net::connector::_internal::PacketPreprocessor::getSingleMessage()
{
  return nullptr;
}
