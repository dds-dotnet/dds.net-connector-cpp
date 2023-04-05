#include "src/internal/inc/variables/var_prim_uword.h"



dds::net::connector::_internal::variables::
  UnsignedWordVariable::UnsignedWordVariable(
    std::string& name,
    Periodicity periodicity,
    UnsignedWordProvider unsignedWordProvider,
    UnsignedWordConsumer unsignedWordConsumer)

  : BasePrimitive(name, PRIMITIVE_TYPE_UNSIGNED_WORD, periodicity)
{
  valueProvider = unsignedWordProvider;
  valueConsumer = unsignedWordConsumer;

  value = 0;
}

const char*
  dds::net::connector::_internal::variables::
  UnsignedWordVariable::getPrintableTypeName()
{
  return "Unsigned Word";
}

void
  dds::net::connector::_internal::variables::
  UnsignedWordVariable::resetValue()
{
  value = 0;
}

bool
  dds::net::connector::_internal::variables::
  UnsignedWordVariable::refreshValue()
{
  if (valueProvider != nullptr)
  {
    unsigned short newValue = valueProvider(name);

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
  UnsignedWordVariable::invokeValueAwaiter()
{
  if (valueConsumer != nullptr)
  {
    valueConsumer(name, value);
  }
}

int
  dds::net::connector::_internal::variables::
  UnsignedWordVariable::getValueSizeOnBuffer()
{
  return 2;
}

void
  dds::net::connector::_internal::variables::
  UnsignedWordVariable::writeValueOnBuffer(BufferAddress buffer, int& offset)
{
  EncDecPrimitive::writeUnsignedWord(buffer, offset, value);
}
