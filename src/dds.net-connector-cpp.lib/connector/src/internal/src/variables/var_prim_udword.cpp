#include "src/internal/inc/variables/var_prim_udword.h"



dds::net::connector::_internal::variables::
  UnsignedDWordVariable::UnsignedDWordVariable(
    std::string& name,
    Periodicity periodicity,
    UnsignedDWordProvider unsignedDWordProvider,
    UnsignedDWordConsumer unsignedDWordConsumer)

  : BasePrimitive(name, PRIMITIVE_TYPE_UNSIGNED_DWORD, periodicity)
{
  valueProvider = unsignedDWordProvider;
  valueConsumer = unsignedDWordConsumer;

  value = 0;
}

const char*
  dds::net::connector::_internal::variables::
  UnsignedDWordVariable::getPrintableTypeName()
{
  return "Unsigned DWord";
}

void
  dds::net::connector::_internal::variables::
  UnsignedDWordVariable::resetValue()
{
  value = 0;
}

bool
  dds::net::connector::_internal::variables::
  UnsignedDWordVariable::refreshValue()
{
  if (valueProvider != nullptr)
  {
    unsigned long newValue = valueProvider(name);

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
  UnsignedDWordVariable::invokeValueAwaiter()
{
  if (valueConsumer != nullptr)
  {
    valueConsumer(name, value);
  }
}

int
  dds::net::connector::_internal::variables::
  UnsignedDWordVariable::getValueSizeOnBuffer()
{
  return 4;
}

void
  dds::net::connector::_internal::variables::
  UnsignedDWordVariable::writeValueOnBuffer(BufferAddress buffer, int& offset)
{
  EncDecPrimitive::writeUnsignedDWord(buffer, offset, value);
}
