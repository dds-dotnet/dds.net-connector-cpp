#include "src/internal/inc/variables/var_prim_string.h"



dds::net::connector::_internal::variables::
  StringVariable::StringVariable(
    std::string& name,
    Periodicity periodicity,
    StringProvider stringProvider,
    StringConsumer stringConsumer)

  : BasePrimitive(name, PRIMITIVE_TYPE_STRING, periodicity)
{
  valueProvider = stringProvider;
  valueConsumer = stringConsumer;

  value = "";
}

const char*
  dds::net::connector::_internal::variables::
  StringVariable::getPrintableTypeName()
{
  return "String";
}

void
  dds::net::connector::_internal::variables::
  StringVariable::resetValue()
{
  value = "";
}

bool
  dds::net::connector::_internal::variables::
  StringVariable::refreshValue()
{
  if (valueProvider != nullptr)
  {
    std::string newValue = valueProvider(name);

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
  StringVariable::invokeValueAwaiter()
{
  if (valueConsumer != nullptr)
  {
    valueConsumer(name, value);
  }
}

int
  dds::net::connector::_internal::variables::
  StringVariable::getValueSizeOnBuffer()
{
  return EncDecPrimitive::getStringSizeOnBuffer(value);
}

void
  dds::net::connector::_internal::variables::
  StringVariable::writeValueOnBuffer(BufferAddress buffer, int& offset)
{
  EncDecPrimitive::writeString(buffer, offset, value);
}
