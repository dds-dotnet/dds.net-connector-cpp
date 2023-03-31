#include "src/internal/inc/variables/base_variable.h"

#include "inc/error.h"
#include "inc/config.h"

#include "src/internal/inc/macros.h"
#include "src/internal/inc/internal_types.h"
#include "src/internal/inc/variables/enc_dec_header.h"

#include <string>

#include <stdio.h>


dds::net::connector::_internal::variables::
  BaseVariable::BaseVariable(
    std::string& name, VariableType variableType, Periodicity periodicity)
{
  this->id = -1;
  this->name = name;
  this->variableType = variableType;
  this->periodicity = periodicity;
}

void
  dds::net::connector::_internal::variables::
  BaseVariable::assignId(int id)
{
  if (this->id != -1)
  {
    char message[200];

#if TARGET_PLATFORM == PLATFORM_WINDOWS
    sprintf_s(message, sizeof(message),
#else
    sprintf(message,
#endif
      "Variable %s has already been assigned with an ID", name.c_str());

    throw Error(message);
  }

  if (id < 0 || id > MAX_USHORT_VALUE)
  {
    char message[200];

#if TARGET_PLATFORM == PLATFORM_WINDOWS
    sprintf_s(message, sizeof(message),
#else
    sprintf(message,
#endif
      "Variable %s cannot be assigned with out-of-range ID %d", name.c_str(), id);

    throw Error(message);
  }

  this->id = id;
}

void
  dds::net::connector::_internal::variables::
  BaseVariable::reset()
{
  id = -1;
  resetValue();
}

int
  dds::net::connector::_internal::variables::
  BaseVariable::getSizeOnBuffer()
{
  return
    EncDecHeader::VARIABLE_ID_SIZE_ON_BUFFER +
    EncDecHeader::VARIABLE_TYPE_SIZE_ON_BUFFER +
    getSubTypeSizeOnBuffer() +
    getValueSizeOnBuffer();
}

void
  dds::net::connector::_internal::variables::
  BaseVariable::writeOnBuffer(BufferAddress buffer, int& offset)
{
  EncDecHeader::writeVariableId(buffer, offset, id);
  EncDecHeader::writeVariableType(buffer, offset, variableType);

  writeSubTypeOnBuffer(buffer, offset);
  writeValueOnBuffer(buffer, offset);
}

