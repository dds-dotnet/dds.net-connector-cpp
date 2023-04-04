#include "src/internal/inc/variables/var_prim_double.h"



dds::net::connector::_internal::variables::
  DoubleVariable::DoubleVariable(
    std::string& name,
    Periodicity periodicity,
    DoubleProvider doubleProvider,
    DoubleConsumer doubleConsumer)

  : BasePrimitive(name, PRIMITIVE_TYPE_DOUBLE, periodicity)
{
  valueProvider = doubleProvider;
  valueConsumer = doubleConsumer;

  value = 0.0;
}

std::string
  dds::net::connector::_internal::variables::
  DoubleVariable::getPrintableTypeName()
{
  return std::string("Double");
}

void
  dds::net::connector::_internal::variables::
  DoubleVariable::resetValue()
{
  value = 0.0;
}

bool
  dds::net::connector::_internal::variables::
  DoubleVariable::refreshValue()
{
  if (valueProvider != nullptr)
  {
    double newValue = valueProvider(name);

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
  DoubleVariable::invokeValueAwaiter()
{
  if (valueConsumer != nullptr)
  {
    valueConsumer(name, value);
  }
}

int
  dds::net::connector::_internal::variables::
  DoubleVariable::getValueSizeOnBuffer()
{
  return 8;
}

void
  dds::net::connector::_internal::variables::
  DoubleVariable::writeValueOnBuffer(BufferAddress buffer, int& offset)
{
  EncDecPrimitive::writeDouble(buffer, offset, value);
}
