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

  data = nullptr;
  dataSize = 0;
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
