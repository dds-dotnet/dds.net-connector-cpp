#include "src/internal/inc/variables/var_prim_boolean.h"


dds::net::connector::_internal::variables::
  BooleanVariable::BooleanVariable(
    std::string& name,
    Periodicity periodicity,
    BooleanProvider booleanProvider,
    BooleanConsumer booleanConsumer)

  : BasePrimitive(name, PRIMITIVE_TYPE_BOOLEAN, periodicity)
{
  valueProvider = booleanProvider;
  valueConsumer = booleanConsumer;

  value = false;
}

std::string
  dds::net::connector::_internal::variables::
  BooleanVariable::getPrintableTypeName()
{
  return std::string("Boolean");
}

void
  dds::net::connector::_internal::variables::
  BooleanVariable::resetValue()
{
  value = false;
}

bool
  dds::net::connector::_internal::variables::
  BooleanVariable::refreshValue()
{
  if (valueProvider != nullptr)
  {
    bool newValue = valueProvider(name);

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
  BooleanVariable::invokeValueAwaiter()
{
  if (valueConsumer != nullptr)
  {
    valueConsumer(name, value);
  }
}

int
  dds::net::connector::_internal::variables::
  BooleanVariable::getValueSizeOnBuffer()
{
  return 1;
}

void
  dds::net::connector::_internal::variables::
  BooleanVariable::writeValueOnBuffer(BufferAddress buffer, int& offset)
{
  EncDecPrimitive::writeBoolean(buffer, offset, value);
}
