#include "src/internal/inc/variables/var_prim_qword.h"



dds::net::connector::_internal::variables::
  QWordVariable::QWordVariable(
    std::string& name,
    Periodicity periodicity,
    QWordProvider qWordProvider,
    QWordConsumer qWordConsumer)

  : BasePrimitive(name, PRIMITIVE_TYPE_QWORD, periodicity)
{
  valueProvider = qWordProvider;
  valueConsumer = qWordConsumer;

  value = 0;
}

std::string
  dds::net::connector::_internal::variables::
  QWordVariable::getPrintableTypeName()
{
  return std::string("QWord");
}

void
  dds::net::connector::_internal::variables::
  QWordVariable::resetValue()
{
  value = 0;
}

bool
  dds::net::connector::_internal::variables::
  QWordVariable::refreshValue()
{
  if (valueProvider != nullptr)
  {
    long long newValue = valueProvider(name);

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
  QWordVariable::invokeValueAwaiter()
{
  if (valueConsumer != nullptr)
  {
    valueConsumer(name, value);
  }
}

int
  dds::net::connector::_internal::variables::
  QWordVariable::getValueSizeOnBuffer()
{
  return 8;
}

void
  dds::net::connector::_internal::variables::
  QWordVariable::writeValueOnBuffer(BufferAddress buffer, int& offset)
{
  EncDecPrimitive::writeQWord(buffer, offset, value);
}
