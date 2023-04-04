#include "src/internal/inc/variables/var_prim_dword.h"



dds::net::connector::_internal::variables::
  DWordVariable::DWordVariable(
    std::string& name,
    Periodicity periodicity,
    DWordProvider dWordProvider,
    DWordConsumer dWordConsumer)

  : BasePrimitive(name, PRIMITIVE_TYPE_DWORD, periodicity)
{
  valueProvider = dWordProvider;
  valueConsumer = dWordConsumer;

  value = 0;
}

std::string
  dds::net::connector::_internal::variables::
  DWordVariable::getPrintableTypeName()
{
  return std::string("DWord");
}

void
  dds::net::connector::_internal::variables::
  DWordVariable::resetValue()
{
  value = 0;
}

bool
  dds::net::connector::_internal::variables::
  DWordVariable::refreshValue()
{
  if (valueProvider != nullptr)
  {
    int newValue = valueProvider(name);

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
  DWordVariable::invokeValueAwaiter()
{
  if (valueConsumer != nullptr)
  {
    valueConsumer(name, value);
  }
}

int
  dds::net::connector::_internal::variables::
  DWordVariable::getValueSizeOnBuffer()
{
  return 4;
}

void
  dds::net::connector::_internal::variables::
  DWordVariable::writeValueOnBuffer(BufferAddress buffer, int& offset)
{
  EncDecPrimitive::writeDWord(buffer, offset, value);
}
