#include "src/internal/inc/variables/var_prim_uqword.h"



dds::net::connector::_internal::variables::
  UnsignedQWordVariable::UnsignedQWordVariable(
    std::string& name,
    Periodicity periodicity,
    UnsignedQWordProvider unsignedQWordProvider,
    UnsignedQWordConsumer unsignedQWordConsumer)

  : BasePrimitive(name, PRIMITIVE_TYPE_UNSIGNED_QWORD, periodicity)
{
  valueProvider = unsignedQWordProvider;
  valueConsumer = unsignedQWordConsumer;

  value = 0;
}

const char*
  dds::net::connector::_internal::variables::
  UnsignedQWordVariable::getPrintableTypeName()
{
  return "Unsigned QWord";
}

void
  dds::net::connector::_internal::variables::
  UnsignedQWordVariable::resetValue()
{
  value = 0;
}

bool
  dds::net::connector::_internal::variables::
  UnsignedQWordVariable::refreshValue()
{
  if (valueProvider != nullptr)
  {
    unsigned long long newValue = valueProvider(name);

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
  UnsignedQWordVariable::invokeValueAwaiter()
{
  if (valueConsumer != nullptr)
  {
    valueConsumer(name, value);
  }
}

int
  dds::net::connector::_internal::variables::
  UnsignedQWordVariable::getValueSizeOnBuffer()
{
  return 8;
}

void
  dds::net::connector::_internal::variables::
  UnsignedQWordVariable::writeValueOnBuffer(BufferAddress buffer, int& offset)
{
  EncDecPrimitive::writeUnsignedQWord(buffer, offset, value);
}
