#include "src/internal/inc/variables/enc_dec_header.h"

#include "inc/config.h"
#include "inc/error.h"


static char message[1024];


void
  dds::net::connector::_internal::variables::
  EncDecHeader::writeMessageHeader(BufferAddress buffer, int& offset, int totalBytes)
{
  buffer[offset++] = '#';
  buffer[offset++] = '#';

  buffer[offset++] = (totalBytes >> 24) & 0x0ff;
  buffer[offset++] = (totalBytes >> 16) & 0x0ff;
  buffer[offset++] = (totalBytes >> 8) & 0x0ff;
  buffer[offset++] = (totalBytes >> 0) & 0x0ff;
}

int
  dds::net::connector::_internal::variables::
  EncDecHeader::readTotalBytesInMessage(BufferAddress buffer, int& offset)
{
  if (buffer[offset] == '#' && buffer[offset + 1] == '#')
  {
    offset += 2;

    int v = buffer[offset++];
    v = (v << 8) | buffer[offset++];
    v = (v << 8) | buffer[offset++];
    v = (v << 8) | buffer[offset++];

    return v;
  }

#if TARGET_PLATFORM == PLATFORM_WINDOWS
  sprintf_s(message, sizeof(message),
#else
  sprintf(message,
#endif
    "The message is not starting from given offset %d", offset);

  throw Error(message);
}

void
  dds::net::connector::_internal::variables::
  EncDecHeader::writePacketId(BufferAddress buffer, int& offset, PacketId id)
{
  int v = (int)id;

  buffer[offset++] = (v >> 8) & 0x0ff;
  buffer[offset++] = (v >> 0) & 0x0ff;
}

PacketId
  dds::net::connector::_internal::variables::
  EncDecHeader::readPacketId(BufferAddress buffer, int& offset)
{
  int v = buffer[offset++];
  v = (v << 8) | buffer[offset++];

  if (v >= 0 && v < PACKET_ID_UNKNOWN)
  {
    return (PacketId)v;
  }

  return PACKET_ID_UNKNOWN;
}



void
  dds::net::connector::_internal::variables::
  EncDecHeader::writeVariableId(BufferAddress buffer, int& offset, int id)
{
  buffer[offset++] = (id >> 8) & 0x0ff;
  buffer[offset++] = (id >> 0) & 0x0ff;
}

int
  dds::net::connector::_internal::variables::
  EncDecHeader::readVariableId(BufferAddress buffer, int& offset)
{
  int value = buffer[offset++];
  value = (value << 8) | buffer[offset++];

  return value;
}



void
  dds::net::connector::_internal::variables::
  EncDecHeader::writeVariableType(BufferAddress buffer, int& offset, VariableType variableType)
{
  int v = (int)variableType;

  buffer[offset++] = (v >> 8) & 0x0ff;
  buffer[offset++] = (v >> 0) & 0x0ff;
}

VariableType
  dds::net::connector::_internal::variables::
  EncDecHeader::readVariableType(BufferAddress buffer, int& offset)
{
  int v = buffer[offset++];
  v = (v << 8) | buffer[offset++];

  if (v >= 0 && v < VARIABLE_TYPE_UNKNOWN)
  {
    return (VariableType)v;
  }

  return VARIABLE_TYPE_UNKNOWN;
}



void
  dds::net::connector::_internal::variables::
  EncDecHeader::writePeriodicity(BufferAddress buffer, int& offset, Periodicity value)
{
  buffer[offset++] = value;
}

Periodicity
  dds::net::connector::_internal::variables::
  EncDecHeader::readPeriodicity(BufferAddress buffer, int& offset)
{
  int v = buffer[offset++];

  if (v >= 0 && v <= LOWEST)
  {
    return (Periodicity)v;
  }

  return ON_CHANGE;
}

