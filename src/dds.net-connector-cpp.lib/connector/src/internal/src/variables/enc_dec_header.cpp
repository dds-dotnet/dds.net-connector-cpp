#include "src/internal/inc/variables/enc_dec_header.h"


void dds::net::connector::_internal::variables::
     EncDecHeader::writePacketId(
       BufferAddress buffer, int& offset, PacketId id)
{
  int v = (int)id;

  buffer[offset++] = (v >> 8) & 0x0ff;
  buffer[offset++] = (v >> 0) & 0x0ff;
}

void dds::net::connector::_internal::variables::
     EncDecHeader::writeVariableId(
       BufferAddress buffer, int& offset, int id)
{
  buffer[offset++] = (id >> 8) & 0x0ff;
  buffer[offset++] = (id >> 0) & 0x0ff;
}

void dds::net::connector::_internal::variables::
     EncDecHeader::writeVariableType(
       BufferAddress buffer, int& offset, VariableType variableType)
{
  int v = (int)variableType;

  buffer[offset++] = (v >> 8) & 0x0ff;
  buffer[offset++] = (v >> 0) & 0x0ff;
}

