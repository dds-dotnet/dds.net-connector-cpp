#include "src/internal/inc/variables/base_primitive.h"

#include "src/internal/inc/variables/enc_dec_primitive.h"


dds::net::connector::_internal::variables::
  BasePrimitive::BasePrimitive(
    std::string& name, PrimitiveType primitiveType, Periodicity periodicity)
  : BaseVariable(name, VARIABLE_TYPE_PRIMITIVE, periodicity)
{
  this->primitiveType = primitiveType;
}

int
  dds::net::connector::_internal::variables::
  BasePrimitive::getSubTypeSizeOnBuffer()
{
  return EncDecPrimitive::PRIMITIVE_TYPE_SIZE_ON_BUFFER;
}

void
  dds::net::connector::_internal::variables::
  BasePrimitive::writeSubTypeOnBuffer(BufferAddress buffer, int& offset)
{
  EncDecPrimitive::writePrimitiveType(buffer, offset, primitiveType);
}

PrimitiveType
  dds::net::connector::_internal::variables::
  BasePrimitive::getPrimitiveType()
{
  return primitiveType;
}
