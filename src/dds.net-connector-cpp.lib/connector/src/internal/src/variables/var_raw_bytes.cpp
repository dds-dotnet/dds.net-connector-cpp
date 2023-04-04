#include "src/internal/inc/variables/var_raw_bytes.h"



dds::net::connector::_internal::variables::
  RawBytesVariable::RawBytesVariable(
    std::string& name,
    Periodicity periodicity,
    RawBytesProvider rawBytesProvider,
    RawBytesConsumer rawBytesConsumer)
  : BaseVariable(name, VARIABLE_TYPE_RAW_BYTES, periodicity)
{
  valueProvider = rawBytesProvider;
  valueConsumer = rawBytesConsumer;
}
