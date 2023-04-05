#include "src/internal/inc/variables/var_prim_single.h"



dds::net::connector::_internal::variables::
  SingleVariable::SingleVariable(
    std::string& name,
    Periodicity periodicity,
    SingleProvider singleProvider,
    SingleConsumer singleConsumer)

  : BasePrimitive(name, PRIMITIVE_TYPE_SINGLE, periodicity)
{
  valueProvider = singleProvider;
  valueConsumer = singleConsumer;

  value = 0.0f;
}

std::string
  dds::net::connector::_internal::variables::
  SingleVariable::getPrintableTypeName()
{
  return std::string("Single");
}

void
  dds::net::connector::_internal::variables::
  SingleVariable::resetValue()
{
  value = 0.0f;
}

bool
  dds::net::connector::_internal::variables::
  SingleVariable::refreshValue()
{
  if (valueProvider != nullptr)
  {
    float newValue = valueProvider(name);

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
  SingleVariable::invokeValueAwaiter()
{
  if (valueConsumer != nullptr)
  {
    valueConsumer(name, value);
  }
}

int
  dds::net::connector::_internal::variables::
  SingleVariable::getValueSizeOnBuffer()
{
  return 4;
}

void
  dds::net::connector::_internal::variables::
  SingleVariable::writeValueOnBuffer(BufferAddress buffer, int& offset)
{
  EncDecPrimitive::writeSingle(buffer, offset, value);
}
