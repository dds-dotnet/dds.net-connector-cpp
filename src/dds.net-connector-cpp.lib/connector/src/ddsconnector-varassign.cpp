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
    "Received boolean cannot be assigned to %s of type %s",
    bpv->name.c_str(), bpv->getPrintableTypeName());

  logger->error(errorMessage);

  return false;
}

bool
  dds::net::connector::
  DdsConnector::updatePrimitiveVariableWithByte(BasePrimitive* bpv, char v)
{
  return false;
}

bool
  dds::net::connector::
  DdsConnector::updatePrimitiveVariableWithWord(BasePrimitive* bpv, short v)
{
  return false;
}

bool
  dds::net::connector::
  DdsConnector::updatePrimitiveVariableWithDWord(BasePrimitive* bpv, long v)
{
  return false;
}

bool
  dds::net::connector::
  DdsConnector::updatePrimitiveVariableWithQWord(BasePrimitive* bpv, long long v)
{
  return false;
}

bool
  dds::net::connector::
  DdsConnector::updatePrimitiveVariableWithUnsignedByte(BasePrimitive* bpv, unsigned char v)
{
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
