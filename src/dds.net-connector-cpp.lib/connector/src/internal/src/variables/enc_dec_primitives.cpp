#include "src/internal/inc/variables/enc_dec_primitives.h"


void
  dds::net::connector::_internal::variables::
  EncDecPrimitives::writePrimitiveType(BufferAddress buffer, int& offset, PrimitiveType value)
{
  buffer[offset++] = value;
}

PrimitiveType
  dds::net::connector::_internal::variables::
  EncDecPrimitives::readPrimitiveType(BufferAddress buffer, int& offset)
{
  int v = buffer[offset++];

  if (v >= 0 && v < PRIMITIVE_TYPE_UNKNOWN)
  {
    return (PrimitiveType)v;
  }

  return PRIMITIVE_TYPE_UNKNOWN;
}
