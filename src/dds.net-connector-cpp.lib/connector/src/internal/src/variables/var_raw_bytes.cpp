#include "src/internal/inc/variables/var_raw_bytes.h"

#include "src/internal/inc/variables/enc_dec_primitive.h"



dds::net::connector::_internal::variables::
  RawBytesVariable::RawBytesVariable(
    std::string& name,
    Periodicity periodicity,
    RawBytesProvider rawBytesProvider,
    RawBytesConsumer rawBytesConsumer,
    BufferManager* bufferManager)
  : BaseVariable(name, VARIABLE_TYPE_RAW_BYTES, periodicity)
{
  valueProvider = rawBytesProvider;
  valueConsumer = rawBytesConsumer;

  data = nullptr;
  dataSize = 0;

  this->bufferManager = bufferManager;
}

std::string
  dds::net::connector::_internal::variables::
  RawBytesVariable::getPrintableTypeName()
{
  return std::string("RawBytes");
}

int
  dds::net::connector::_internal::variables::
  RawBytesVariable::getSubTypeSizeOnBuffer()
{
  //- 
  //- We do not have any sub-types here, unlike the primitive types.
  //- Therefore, its sub-type will take "0" bytes on the data buffer.
  //- 

  return 0;
}

void
  dds::net::connector::_internal::variables::
  RawBytesVariable::writeSubTypeOnBuffer(BufferAddress buffer, int& offset)
{
  //- 
  //- We do not have any sub-types here, unlike the primitive types.
  //- So, we do not write anything.
  //- 
}

void
  dds::net::connector::_internal::variables::
  RawBytesVariable::resetValue()
{
  data = nullptr;
  dataSize = 0;
}

void
  dds::net::connector::_internal::variables::
  RawBytesVariable::writeValueOnBuffer(BufferAddress buffer, int& offset)
{
  if (data != nullptr && dataSize > 0)
  {
    EncDecPrimitive::writeUnsignedDWord(buffer, offset, dataSize);

    for (int i = 0; i < dataSize; i++)
    {
      buffer[offset++] = data[i];
    }
  }
  else
  {
    EncDecPrimitive::writeUnsignedDWord(buffer, offset, 0);
  }
}

bool
  dds::net::connector::_internal::variables::
  RawBytesVariable::updateData(BufferAddress buffer, int size)
{
  if (buffer == nullptr)
  {
    if (data == nullptr)
    {
      return false;
    }
    else
    {
      delete data;

      data = nullptr;
      dataSize = 0;

      return true;
    }
  }
  else
  {
    if (data == nullptr)
    {
      data = (unsigned char*)buffer;
      dataSize = size;
      return true;
    }
    else
    {
      if (dataSize != size)
      {
        delete data;

        data = (unsigned char*)buffer;
        dataSize = size;

        return true;
      }
      else
      {
        bool isDiff = false;

        for (int i = 0; i < dataSize; i++)
        {
          if ((unsigned char)data[i] != ((unsigned char*)buffer)[i])
          {
            isDiff = true;
          }

          data[i] = ((unsigned char*)buffer)[i];
        }

        return isDiff;
      }
    }
  }
}
