#include "inc/ddsconnector.h"

#include "inc/error.h"

#include "src/internal/inc/internal_types.h"
#include "src/internal/inc/buffer_manager.h"

#include "src/internal/inc/variables/base_variable.h"
#include "src/internal/inc/variables/base_primitive.h"
#include "src/internal/inc/variables/var_prim_boolean.h"
#include "src/internal/inc/variables/var_prim_byte.h"
#include "src/internal/inc/variables/var_prim_double.h"
#include "src/internal/inc/variables/var_prim_dword.h"
#include "src/internal/inc/variables/var_prim_qword.h"
#include "src/internal/inc/variables/var_prim_single.h"
#include "src/internal/inc/variables/var_prim_string.h"
#include "src/internal/inc/variables/var_prim_ubyte.h"
#include "src/internal/inc/variables/var_prim_udword.h"
#include "src/internal/inc/variables/var_prim_uqword.h"
#include "src/internal/inc/variables/var_prim_uword.h"
#include "src/internal/inc/variables/var_prim_word.h"
#include "src/internal/inc/variables/var_raw_bytes.h"

#include <string>
#include <exception>


using namespace std;
using namespace dds::net::connector::_internal::variables;


static char errorMessage[2048];


bool
  dds::net::connector::
  DdsConnector::updatePrimitiveVariableWithString(BasePrimitive* bpv, std::string& v)
{
  if (bpv->primitiveType == PRIMITIVE_TYPE_STRING)
  {
    StringVariable* str = (StringVariable*)bpv;

    if (str->value != v)
    {
      str->value = v;
      return true;
    }
    else
    {
      return false;
    }
  }

#if TARGET_PLATFORM == PLATFORM_WINDOWS
  sprintf_s(errorMessage, sizeof(errorMessage),
#else
  sprintf(errorMessage,
#endif
    "Received string %s cannot be assigned to %s of type %s",
    v.c_str(), bpv->name.c_str(), bpv->getPrintableTypeName());

  logger->error(errorMessage);

  return false;
}

bool
  dds::net::connector::
  DdsConnector::updatePrimitiveVariableWithBoolean(BasePrimitive* bpv, bool v)
{
  if (bpv->primitiveType == PRIMITIVE_TYPE_BOOLEAN)
  {
    BooleanVariable* bl = (BooleanVariable*)bpv;

    if (bl->value != v)
    {
      bl->value = v;
      return true;
    }
    else
    {
      return false;
    }
  }

#if TARGET_PLATFORM == PLATFORM_WINDOWS
  sprintf_s(errorMessage, sizeof(errorMessage),
#else
  sprintf(errorMessage,
#endif
    "Received Boolean cannot be assigned to %s of type %s",
    bpv->name.c_str(), bpv->getPrintableTypeName());

  logger->error(errorMessage);

  return false;
}

bool
  dds::net::connector::
  DdsConnector::updatePrimitiveVariableWithByte(BasePrimitive* bpv, char v)
{
  if (bpv->primitiveType == PRIMITIVE_TYPE_BYTE)
  {
    ByteVariable* bt = (ByteVariable*)bpv;

    if (bt->value != v)
    {
      bt->value = v;
      return true;
    }
    else
    {
      return false;
    }
  }
  else if (bpv->primitiveType == PRIMITIVE_TYPE_WORD)
  {
    WordVariable* wrd = (WordVariable*)bpv;

    if (wrd->value != v)
    {
      wrd->value = v;
      return true;
    }
    else
    {
      return false;
    }
  }
  else if (bpv->primitiveType == PRIMITIVE_TYPE_DWORD)
  {
    DWordVariable* dwrd = (DWordVariable*)bpv;

    if (dwrd->value != v)
    {
      dwrd->value = v;
      return true;
    }
    else
    {
      return false;
    }
  }
  else if (bpv->primitiveType == PRIMITIVE_TYPE_QWORD)
  {
    QWordVariable* qwrd = (QWordVariable*)bpv;

    if (qwrd->value != v)
    {
      qwrd->value = v;
      return true;
    }
    else
    {
      return false;
    }
  }
  else if (bpv->primitiveType == PRIMITIVE_TYPE_SINGLE)
  {
    SingleVariable* sngl = (SingleVariable*)bpv;

    if (sngl->value != v)
    {
      sngl->value = v;
      return true;
    }
    else
    {
      return false;
    }
  }
  else if (bpv->primitiveType == PRIMITIVE_TYPE_DOUBLE)
  {
    DoubleVariable* dbl = (DoubleVariable*)bpv;

    if (dbl->value != v)
    {
      dbl->value = v;
      return true;
    }
    else
    {
      return false;
    }
  }

#if TARGET_PLATFORM == PLATFORM_WINDOWS
  sprintf_s(errorMessage, sizeof(errorMessage),
#else
  sprintf(errorMessage,
#endif
    "Received Byte cannot be assigned to %s of type %s",
    bpv->name.c_str(), bpv->getPrintableTypeName());

  logger->error(errorMessage);

  return false;
}

bool
  dds::net::connector::
  DdsConnector::updatePrimitiveVariableWithWord(BasePrimitive* bpv, short v)
{
  if (bpv->primitiveType == PRIMITIVE_TYPE_WORD)
  {
    WordVariable* wrd = (WordVariable*)bpv;

    if (wrd->value != v)
    {
      wrd->value = v;
      return true;
    }
    else
    {
      return false;
    }
  }
  else if (bpv->primitiveType == PRIMITIVE_TYPE_DWORD)
  {
    DWordVariable* dwrd = (DWordVariable*)bpv;

    if (dwrd->value != v)
    {
      dwrd->value = v;
      return true;
    }
    else
    {
      return false;
    }
  }
  else if (bpv->primitiveType == PRIMITIVE_TYPE_QWORD)
  {
    QWordVariable* qwrd = (QWordVariable*)bpv;

    if (qwrd->value != v)
    {
      qwrd->value = v;
      return true;
    }
    else
    {
      return false;
    }
  }
  else if (bpv->primitiveType == PRIMITIVE_TYPE_SINGLE)
  {
    SingleVariable* sngl = (SingleVariable*)bpv;

    if (sngl->value != v)
    {
      sngl->value = v;
      return true;
    }
    else
    {
      return false;
    }
  }
  else if (bpv->primitiveType == PRIMITIVE_TYPE_DOUBLE)
  {
    DoubleVariable* dbl = (DoubleVariable*)bpv;

    if (dbl->value != v)
    {
      dbl->value = v;
      return true;
    }
    else
    {
      return false;
    }
  }

#if TARGET_PLATFORM == PLATFORM_WINDOWS
  sprintf_s(errorMessage, sizeof(errorMessage),
#else
  sprintf(errorMessage,
#endif
    "Received Word cannot be assigned to %s of type %s",
    bpv->name.c_str(), bpv->getPrintableTypeName());

  logger->error(errorMessage);

  return false;
}

bool
  dds::net::connector::
  DdsConnector::updatePrimitiveVariableWithDWord(BasePrimitive* bpv, long v)
{
  if (bpv->primitiveType == PRIMITIVE_TYPE_DWORD)
  {
    DWordVariable* dwrd = (DWordVariable*)bpv;

    if (dwrd->value != v)
    {
      dwrd->value = v;
      return true;
    }
    else
    {
      return false;
    }
  }
  else if (bpv->primitiveType == PRIMITIVE_TYPE_QWORD)
  {
    QWordVariable* qwrd = (QWordVariable*)bpv;

    if (qwrd->value != v)
    {
      qwrd->value = v;
      return true;
    }
    else
    {
      return false;
    }
  }
  else if (bpv->primitiveType == PRIMITIVE_TYPE_SINGLE)
  {
    SingleVariable* sngl = (SingleVariable*)bpv;

    float conv = v;
    bool ret = false;

    if (sngl->value != conv)
    {
      sngl->value = conv;
      ret = true;
    }

    return ret;
  }
  else if (bpv->primitiveType == PRIMITIVE_TYPE_DOUBLE)
  {
    DoubleVariable* dbl = (DoubleVariable*)bpv;

    if (dbl->value != v)
    {
      dbl->value = v;
      return true;
    }
    else
    {
      return false;
    }
  }

#if TARGET_PLATFORM == PLATFORM_WINDOWS
  sprintf_s(errorMessage, sizeof(errorMessage),
#else
  sprintf(errorMessage,
#endif
    "Received DWord cannot be assigned to %s of type %s",
    bpv->name.c_str(), bpv->getPrintableTypeName());

  logger->error(errorMessage);

  return false;
}

bool
  dds::net::connector::
  DdsConnector::updatePrimitiveVariableWithQWord(BasePrimitive* bpv, long long v)
{
  if (bpv->primitiveType == PRIMITIVE_TYPE_QWORD)
  {
    QWordVariable* qwrd = (QWordVariable*)bpv;

    if (qwrd->value != v)
    {
      qwrd->value = v;
      return true;
    }
    else
    {
      return false;
    }
  }
  else if (bpv->primitiveType == PRIMITIVE_TYPE_DOUBLE)
  {
    DoubleVariable* dbl = (DoubleVariable*)bpv;

    if (dbl->value != v)
    {
      dbl->value = v;
      return true;
    }
    else
    {
      return false;
    }
  }

#if TARGET_PLATFORM == PLATFORM_WINDOWS
  sprintf_s(errorMessage, sizeof(errorMessage),
#else
  sprintf(errorMessage,
#endif
    "Received QWord cannot be assigned to %s of type %s",
    bpv->name.c_str(), bpv->getPrintableTypeName());

  logger->error(errorMessage);

  return false;
}

bool
  dds::net::connector::
  DdsConnector::updatePrimitiveVariableWithUnsignedByte(BasePrimitive* bpv, unsigned char v)
{
  if (bpv->primitiveType == PRIMITIVE_TYPE_WORD)
  {
    WordVariable* wrd = (WordVariable*)bpv;

    if (wrd->value != v)
    {
      wrd->value = v;
      return true;
    }
    else
    {
      return false;
    }
  }
  else if (bpv->primitiveType == PRIMITIVE_TYPE_DWORD)
  {
    DWordVariable* dwrd = (DWordVariable*)bpv;

    if (dwrd->value != v)
    {
      dwrd->value = v;
      return true;
    }
    else
    {
      return false;
    }
  }
  else if (bpv->primitiveType == PRIMITIVE_TYPE_QWORD)
  {
    QWordVariable* qwrd = (QWordVariable*)bpv;

    if (qwrd->value != v)
    {
      qwrd->value = v;
      return true;
    }
    else
    {
      return false;
    }
  }
  else if (bpv->primitiveType == PRIMITIVE_TYPE_UNSIGNED_BYTE)
  {
    UnsignedByteVariable* ubt = (UnsignedByteVariable*)bpv;

    if (ubt->value != v)
    {
      ubt->value = v;
      return true;
    }
    else
    {
      return false;
    }
  }
  else if (bpv->primitiveType == PRIMITIVE_TYPE_UNSIGNED_WORD)
  {
    UnsignedWordVariable* uwrd = (UnsignedWordVariable*)bpv;

    if (uwrd->value != v)
    {
      uwrd->value = v;
      return true;
    }
    else
    {
      return false;
    }
  }
  else if (bpv->primitiveType == PRIMITIVE_TYPE_UNSIGNED_DWORD)
  {
    UnsignedDWordVariable* udwrd = (UnsignedDWordVariable*)bpv;

    if (udwrd->value != v)
    {
      udwrd->value = v;
      return true;
    }
    else
    {
      return false;
    }
  }
  else if (bpv->primitiveType == PRIMITIVE_TYPE_UNSIGNED_QWORD)
  {
    UnsignedQWordVariable* uqwrd = (UnsignedQWordVariable*)bpv;

    if (uqwrd->value != v)
    {
      uqwrd->value = v;
      return true;
    }
    else
    {
      return false;
    }
  }
  else if (bpv->primitiveType == PRIMITIVE_TYPE_SINGLE)
  {
    SingleVariable* sngl = (SingleVariable*)bpv;

    if (sngl->value != v)
    {
      sngl->value = v;
      return true;
    }
    else
    {
      return false;
    }
  }
  else if (bpv->primitiveType == PRIMITIVE_TYPE_DOUBLE)
  {
    DoubleVariable* dbl = (DoubleVariable*)bpv;

    if (dbl->value != v)
    {
      dbl->value = v;
      return true;
    }
    else
    {
      return false;
    }
  }

#if TARGET_PLATFORM == PLATFORM_WINDOWS
  sprintf_s(errorMessage, sizeof(errorMessage),
#else
  sprintf(errorMessage,
#endif
    "Received Unsigned Byte cannot be assigned to %s of type %s",
    bpv->name.c_str(), bpv->getPrintableTypeName());

  logger->error(errorMessage);

  return false;
}

bool
  dds::net::connector::
  DdsConnector::updatePrimitiveVariableWithUnsignedWord(BasePrimitive* bpv, unsigned short v)
{
  return false;
}

bool
  dds::net::connector::
  DdsConnector::updatePrimitiveVariableWithUnsignedDWord(BasePrimitive* bpv, unsigned long v)
{
  return false;
}

bool
  dds::net::connector::
  DdsConnector::updatePrimitiveVariableWithUnsignedQWord(BasePrimitive* bpv, unsigned long long v)
{
  return false;
}

bool
  dds::net::connector::
  DdsConnector::updatePrimitiveVariableWithSingle(BasePrimitive* bpv, float v)
{
  return false;
}

bool
  dds::net::connector::
  DdsConnector::updatePrimitiveVariableWithDouble(BasePrimitive* bpv, double v)
{
  return false;
}
