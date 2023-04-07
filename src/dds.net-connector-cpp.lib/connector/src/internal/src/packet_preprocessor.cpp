#include "src/internal/inc/packet_preprocessor.h"

#include "src/internal/inc/buffer_manager.h"
#include "src/internal/inc/packet_from_server.h"



dds::net::connector::_internal::
  PacketPreprocessor::PacketPreprocessor(BufferManager* bufferManager)
{
  this->bufferManager = bufferManager;

  this->previousData = nullptr;
  this->previousDataSize = 0;
  this->previousDataStartIndex = 0;
  this->previousNextWriteIndex = 0;
}

dds::net::connector::_internal::
  PacketPreprocessor::~PacketPreprocessor()
{
  if (previousData != nullptr)
  {
    bufferManager->free(previousData);
}
}

void
  dds::net::connector::_internal::
  PacketPreprocessor::addData(PacketFromServer* packet)
{

  delete packet;
}

BufferAddress
  dds::net::connector::_internal::
  PacketPreprocessor::getSingleMessage(int& size)
{
  return nullptr;
}
