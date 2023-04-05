#include "src/internal/inc/variables/var_prim_word.h"



dds::net::connector::_internal::variables::
  WordVariable::WordVariable(
    std::string& name,
    Periodicity periodicity,
    WordProvider wordProvider,
    WordConsumer wordConsumer)

  : BasePrimitive(name, PRIMITIVE_TYPE_WORD, periodicity)
{
  valueProvider = wordProvider;
  valueConsumer = wordConsumer;

  value = 0;
}

std::string
  dds::net::connector::_internal::variables::
  WordVariable::getPrintableTypeName()
{
  return std::string("Word");
}

void
  dds::net::connector::_internal::variables::
  WordVariable::resetValue()
{
  value = 0;
}

bool
  dds::net::connector::_internal::variables::
  WordVariable::refreshValue()
{
  if (valueProvider != nullptr)
  {
    short newValue = valueProvider(name);

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
  WordVariable::invokeValueAwaiter()
{
  if (valueConsumer != nullptr)
  {
    valueConsumer(name, value);
  }
}

int
  dds::net::connector::_internal::variables::
  WordVariable::getValueSizeOnBuffer()
{
  return 2;
}

void
  dds::net::connector::_internal::variables::
  WordVariable::writeValueOnBuffer(BufferAddress buffer, int& offset)
{
  EncDecPrimitive::writeWord(buffer, offset, value);
}
