#include "src/internal/inc/variables/var_prim_ubyte.h"



dds::net::connector::_internal::variables::
  UnsignedByteVariable::UnsignedByteVariable(
    std::string& name,
    Periodicity periodicity,
    UnsignedByteProvider unsignedByteProvider,
    UnsignedByteConsumer unsignedByteConsumer)

  : BasePrimitive(name, PRIMITIVE_TYPE_UNSIGNED_BYTE, periodicity)
{
  valueProvider = unsignedByteProvider;
  valueConsumer = unsignedByteConsumer;

  value = 0;
}

std::string
  dds::net::connector::_internal::variables::
  UnsignedByteVariable::getPrintableTypeName()
{
  return std::string("Unsigned Byte");
}

void
  dds::net::connector::_internal::variables::
  UnsignedByteVariable::resetValue()
{
  value = 0;
}

bool
  dds::net::connector::_internal::variables::
  UnsignedByteVariable::refreshValue()
{
  if (valueProvider != nullptr)
  {
    unsigned char newValue = valueProvider(name);

    if (value != newValue)
    {
      value = newValue;
      return true;
    }
  }

  return false;
}

void
  dds::net::connector::_internal::variables::
  UnsignedByteVariable::invokeValueAwaiter()
{
  if (valueConsumer != nullptr)
  {
    valueConsumer(name, value);
  }
}

int
  dds::net::connector::_internal::variables::
  UnsignedByteVariable::getValueSizeOnBuffer()
{
  return 1;
}

void
  dds::net::connector::_internal::variables::
  UnsignedByteVariable::writeValueOnBuffer(BufferAddress buffer, int& offset)
{
  EncDecPrimitive::writeUnsignedByte(buffer, offset, value);
}
