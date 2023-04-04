#include "src/internal/inc/variables/enc_dec_primitive.h"

#include <codecvt>
#include <locale>


PrimitiveType
  dds::net::connector::_internal::variables::
  EncDecPrimitive::readPrimitiveType(BufferAddress buffer, int& offset)
{
  int v = buffer[offset++];

  if (v >= 0 && v < PRIMITIVE_TYPE_UNKNOWN)
  {
    return (PrimitiveType)v;
  }

  return PRIMITIVE_TYPE_UNKNOWN;
}

void
  dds::net::connector::_internal::variables::
  EncDecPrimitive::writePrimitiveType(BufferAddress buffer, int& offset, PrimitiveType value)
{
  buffer[offset++] = value;
}



int
  dds::net::connector::_internal::variables::
  EncDecPrimitive::getStringSizeOnBuffer(std::string& s)
{
  std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> u16Converter;
  std::u16string u16 = u16Converter.from_bytes(s);
  return u16.size() * 2;
}

std::string&
  dds::net::connector::_internal::variables::
  EncDecPrimitive::readString(BufferAddress buffer, int& offset)
{
  /*int length = buffer[offset++];
  length = (length << 8) | buffer[offset++];

  std::string retval = Encoding.Unicode.GetString(data, offset, length);
  offset += length;

  return retval;*/
}

void
  dds::net::connector::_internal::variables::
  EncDecPrimitive::writeString(BufferAddress buffer, int& offset, std::string& value)
{
  std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> u16Converter;
  std::u16string u16 = u16Converter.from_bytes(value);

  buffer[offset + 0] = (u16.size() >> 8) & 0x0ff;
  buffer[offset + 1] = u16.size() & 0x0ff;

  offset += 2;

  if (u16.size() > 0)
  {
    for (int i = 0; i < (int)u16.size(); i++)
    {
      unsigned short v = u16[i];

      // Writing in little-endian format.

      buffer[offset++] = (v >> 0) & 0x0ff;
      buffer[offset++] = (v >> 8) & 0x0ff;
    }
  }
}



bool
  dds::net::connector::_internal::variables::
  EncDecPrimitive::readBoolean(BufferAddress buffer, int& offset)
{
  return buffer[offset++] != 0;
}

void
  dds::net::connector::_internal::variables::
  EncDecPrimitive::writeBoolean(BufferAddress buffer, int& offset, bool value)
{
  buffer[offset++] = value ? 1 : 0;
}



char
  dds::net::connector::_internal::variables::
  EncDecPrimitive::readByte(BufferAddress buffer, int& offset)
{
  return buffer[offset++];
}

void
  dds::net::connector::_internal::variables::
  EncDecPrimitive::writeByte(BufferAddress buffer, int& offset, char value)
{
  buffer[offset++] = value;
}



short
  dds::net::connector::_internal::variables::
  EncDecPrimitive::readWord(BufferAddress buffer, int& offset)
{
  int value = buffer[offset++];
  value = (value << 8) | buffer[offset++];

  return (short)value;
}

void
  dds::net::connector::_internal::variables::
  EncDecPrimitive::writeWord(BufferAddress buffer, int& offset, short value)
{
  buffer[offset++] = (value >> 8) & 0x0ff;
  buffer[offset++] = value & 0x0ff;
}



long
  dds::net::connector::_internal::variables::
  EncDecPrimitive::readDWord(BufferAddress buffer, int& offset)
{
  long value = buffer[offset++];
  value = (value << 8) | buffer[offset++];
  value = (value << 8) | buffer[offset++];
  value = (value << 8) | buffer[offset++];

  return value;
}

void
  dds::net::connector::_internal::variables::
  EncDecPrimitive::writeDWord(BufferAddress buffer, int& offset, long value)
{
  buffer[offset++] = (value >> 24) & 0x0ff;
  buffer[offset++] = (value >> 16) & 0x0ff;
  buffer[offset++] = (value >> 8) & 0x0ff;
  buffer[offset++] = (value >> 0) & 0x0ff;
}



long long
  dds::net::connector::_internal::variables::
  EncDecPrimitive::readQWord(BufferAddress buffer, int& offset)
{
  long long value = buffer[offset++];
  value = (value << 8) | buffer[offset++];
  value = (value << 8) | buffer[offset++];
  value = (value << 8) | buffer[offset++];
  value = (value << 8) | buffer[offset++];
  value = (value << 8) | buffer[offset++];
  value = (value << 8) | buffer[offset++];
  value = (value << 8) | buffer[offset++];

  return value;
}

void
  dds::net::connector::_internal::variables::
  EncDecPrimitive::writeQWord(BufferAddress buffer, int& offset, long long value)
{
  buffer[offset++] = (value >> 56) & 0x0ff;
  buffer[offset++] = (value >> 48) & 0x0ff;
  buffer[offset++] = (value >> 40) & 0x0ff;
  buffer[offset++] = (value >> 32) & 0x0ff;
  buffer[offset++] = (value >> 24) & 0x0ff;
  buffer[offset++] = (value >> 16) & 0x0ff;
  buffer[offset++] = (value >> 8) & 0x0ff;
  buffer[offset++] = (value >> 0) & 0x0ff;
}



unsigned char
  dds::net::connector::_internal::variables::
  EncDecPrimitive::readUnsignedByte(BufferAddress buffer, int& offset)
{
  return (unsigned char)buffer[offset++];
}

void
  dds::net::connector::_internal::variables::
  EncDecPrimitive::writeUnsignedByte(BufferAddress buffer, int& offset, unsigned char value)
{
  buffer[offset++] = value;
}



unsigned short
  dds::net::connector::_internal::variables::
  EncDecPrimitive::readUnsignedWord(BufferAddress buffer, int& offset)
{
  unsigned short value = buffer[offset++];
  value = (value << 8) | buffer[offset++];

  return value;
}

void
  dds::net::connector::_internal::variables::
  EncDecPrimitive::writeUnsignedWord(BufferAddress buffer, int& offset, unsigned short value)
{
  buffer[offset++] = (value >> 8) & 0x0ff;
  buffer[offset++] = (value >> 0) & 0x0ff;
}



unsigned long
  dds::net::connector::_internal::variables::
  EncDecPrimitive::readUnsignedDWord(BufferAddress buffer, int& offset)
{
  unsigned long value = buffer[offset++];
  value = (value << 8) | buffer[offset++];
  value = (value << 8) | buffer[offset++];
  value = (value << 8) | buffer[offset++];

  return value;
}

void
  dds::net::connector::_internal::variables::
  EncDecPrimitive::writeUnsignedDWord(BufferAddress buffer, int& offset, unsigned long value)
{
  buffer[offset++] = (value >> 24) & 0x0ff;
  buffer[offset++] = (value >> 16) & 0x0ff;
  buffer[offset++] = (value >> 8) & 0x0ff;
  buffer[offset++] = (value >> 0) & 0x0ff;
}



unsigned long long
  dds::net::connector::_internal::variables::
  EncDecPrimitive::readUnsignedQWord(BufferAddress buffer, int& offset)
{
  unsigned long long value = buffer[offset++];
  value = (value << 8) | buffer[offset++];
  value = (value << 8) | buffer[offset++];
  value = (value << 8) | buffer[offset++];
  value = (value << 8) | buffer[offset++];
  value = (value << 8) | buffer[offset++];
  value = (value << 8) | buffer[offset++];
  value = (value << 8) | buffer[offset++];

  return value;
}

void
  dds::net::connector::_internal::variables::
  EncDecPrimitive::writeUnsignedQWord(BufferAddress buffer, int& offset, unsigned long long value)
{
  buffer[offset++] = (value >> 56) & 0x0ff;
  buffer[offset++] = (value >> 48) & 0x0ff;
  buffer[offset++] = (value >> 40) & 0x0ff;
  buffer[offset++] = (value >> 32) & 0x0ff;
  buffer[offset++] = (value >> 24) & 0x0ff;
  buffer[offset++] = (value >> 16) & 0x0ff;
  buffer[offset++] = (value >> 8) & 0x0ff;
  buffer[offset++] = (value >> 0) & 0x0ff;
}



float
  dds::net::connector::_internal::variables::
  EncDecPrimitive::readSingle(BufferAddress buffer, int& offset)
{
  float value;
  
  unsigned char* p = (unsigned char*)&value;

  if (isLittleEndian())
  {
    p[0] = buffer[offset + 3];
    p[1] = buffer[offset + 2];
    p[2] = buffer[offset + 1];
    p[3] = buffer[offset + 0]; // MSB
  }
  else
  {
    p[0] = buffer[offset + 0]; // MSB
    p[1] = buffer[offset + 1];
    p[2] = buffer[offset + 2];
    p[3] = buffer[offset + 3];
  }
  
  offset += 4;

  return value;
}

void
  dds::net::connector::_internal::variables::
  EncDecPrimitive::writeSingle(BufferAddress buffer, int& offset, float value)
{
  unsigned char* p = (unsigned char*)&value;

  if (isLittleEndian())
  {
    for (int i = 3; i >= 0; i--)
    {
      buffer[offset++] = p[i];
    }
  }
  else
  {
    for (int i = 0; i < 4; i++)
    {
      buffer[offset++] = p[i];
    }
  }
}



double
  dds::net::connector::_internal::variables::
  EncDecPrimitive::readDouble(BufferAddress buffer, int& offset)
{
  double value;

  unsigned char* p = (unsigned char*)&value;

  if (isLittleEndian())
  {
    p[0] = buffer[offset + 7];
    p[1] = buffer[offset + 6];
    p[2] = buffer[offset + 5];
    p[3] = buffer[offset + 4];
    p[4] = buffer[offset + 3];
    p[5] = buffer[offset + 2];
    p[6] = buffer[offset + 1];
    p[7] = buffer[offset + 0]; // MSB
  }
  else
  {
    p[0] = buffer[offset + 0]; // MSB
    p[1] = buffer[offset + 1];
    p[2] = buffer[offset + 2];
    p[3] = buffer[offset + 3];
    p[4] = buffer[offset + 4];
    p[5] = buffer[offset + 5];
    p[6] = buffer[offset + 6];
    p[7] = buffer[offset + 7];
  }

  offset += 8;

  return value;
}

void
  dds::net::connector::_internal::variables::
  EncDecPrimitive::writeDouble(BufferAddress buffer, int& offset, double value)
{
  unsigned char* p = (unsigned char*)&value;

  if (isLittleEndian())
  {
    for (int i = 7; i >= 0; i--)
    {
      buffer[offset++] = p[i];
    }
  }
  else
  {
    for (int i = 0; i < 8; i++)
    {
      buffer[offset++] = p[i];
    }
  }
}




static unsigned short test_value = 0x00AA;

bool
  dds::net::connector::_internal::variables::
  EncDecPrimitive::isLittleEndian()
{
  unsigned char* p = (unsigned char*)&test_value;

  if (*p == 0xAA)
    return true;

  return false;
}

