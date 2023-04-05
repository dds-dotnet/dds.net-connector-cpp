#include "src/internal/inc/variables/var_prim_byte.h"



dds::net::connector::_internal::variables::
  ByteVariable::ByteVariable(
    std::string& name,
    Periodicity periodicity,
    ByteProvider byteProvider,
    ByteConsumer byteConsumer)

  : BasePrimitive(name, PRIMITIVE_TYPE_BYTE, periodicity)
{
  valueProvider = byteProvider;
  valueConsumer = byteConsumer;

  value = 0;
}

const char*
  dds::net::connector::_internal::variables::
  ByteVariable::getPrintableTypeName()
{
  return "Byte";
}

void
  dds::net::connector::_internal::variables::
  ByteVariable::resetValue()
{
  value = 0;
}

bool
  dds::net::connector::_internal::variables::
  ByteVariable::refreshValue()
{
  if (valueProvider != nullptr)
  {
    char newValue = valueProvider(name);

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
  ByteVariable::invokeValueAwaiter()
{
  if (valueConsumer != nullptr)
  {
    valueConsumer(name, value);
  }
}

int
  dds::net::connector::_internal::variables::
  ByteVariable::getValueSizeOnBuffer()
{
  return 1;
}

void
  dds::net::connector::_internal::variables::
  ByteVariable::writeValueOnBuffer(BufferAddress buffer, int& offset)
{
  EncDecPrimitive::writeByte(buffer, offset, value);
}
