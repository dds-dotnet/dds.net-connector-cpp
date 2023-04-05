#include "inc/ddsconnector.h"

#include "inc/error.h"

#include "src/internal/inc/macros.h"
#include "src/internal/inc/internal_types.h"
#include "src/internal/inc/string_helper.h"
#include "src/internal/inc/buffer_manager.h"
#include "src/internal/inc/threaded_network_client.h"
#include "src/internal/inc/network_client.h"
#include "src/internal/inc/easy_thread.h"

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



using namespace dds::net::connector::_internal::variables;

static char message[1024];

/*************************************************************************************/
/*                                                                                   */
/* Registering:                                                                      */
/*     - Providers                                                                   */
/*                                                                                   */
/*************************************************************************************/

void
dds::net::connector::
DdsConnector::registerStringProvider(
  std::string variableName, StringProvider provider, Periodicity periodicity)
{
  variablesLock.lock();
  {
    if (uploadVariables.count(variableName) > 0 ||
        uploadVariablesToBeRegistered.count(variableName) > 0)
    {
#if TARGET_PLATFORM == PLATFORM_WINDOWS
      sprintf_s(message, sizeof(message),
#else
      sprintf(message,
#endif
        "The variable named %s has already been registered for provision to the server.", variableName.c_str());
      variablesLock.unlock();
      throw Error(message);
    }
    else
    {
      uploadVariablesToBeRegistered[variableName] = new StringVariable(variableName, periodicity, provider, nullptr);
    }
  }
  variablesLock.unlock();
}

void
dds::net::connector::
DdsConnector::registerBooleanProvider(
  std::string variableName, BooleanProvider provider, Periodicity periodicity)
{
  variablesLock.lock();
  {
    if (uploadVariables.count(variableName) > 0 ||
      uploadVariablesToBeRegistered.count(variableName) > 0)
    {
#if TARGET_PLATFORM == PLATFORM_WINDOWS
      sprintf_s(message, sizeof(message),
#else
      sprintf(message,
#endif
        "The variable named %s has already been registered for provision to the server.", variableName.c_str());
      variablesLock.unlock();
      throw Error(message);
    }
    else
    {
      uploadVariablesToBeRegistered[variableName] = new BooleanVariable(variableName, periodicity, provider, nullptr);
    }
  }
  variablesLock.unlock();
}

void
dds::net::connector::
DdsConnector::registerByteProvider(
  std::string variableName, ByteProvider provider, Periodicity periodicity)
{
  variablesLock.lock();
  {
    if (uploadVariables.count(variableName) > 0 ||
      uploadVariablesToBeRegistered.count(variableName) > 0)
    {
#if TARGET_PLATFORM == PLATFORM_WINDOWS
      sprintf_s(message, sizeof(message),
#else
      sprintf(message,
#endif
        "The variable named %s has already been registered for provision to the server.", variableName.c_str());
      variablesLock.unlock();
      throw Error(message);
    }
    else
    {
      uploadVariablesToBeRegistered[variableName] = new ByteVariable(variableName, periodicity, provider, nullptr);
    }
  }
  variablesLock.unlock();
}

void
dds::net::connector::
DdsConnector::registerWordProvider(
  std::string variableName, WordProvider provider, Periodicity periodicity)
{
  variablesLock.lock();
  {
    if (uploadVariables.count(variableName) > 0 ||
      uploadVariablesToBeRegistered.count(variableName) > 0)
    {
#if TARGET_PLATFORM == PLATFORM_WINDOWS
      sprintf_s(message, sizeof(message),
#else
      sprintf(message,
#endif
        "The variable named %s has already been registered for provision to the server.", variableName.c_str());
      variablesLock.unlock();
      throw Error(message);
    }
    else
    {
      uploadVariablesToBeRegistered[variableName] = new WordVariable(variableName, periodicity, provider, nullptr);
    }
  }
  variablesLock.unlock();
}

void
dds::net::connector::
DdsConnector::registerDWordProvider(
  std::string variableName, DWordProvider provider, Periodicity periodicity)
{
  variablesLock.lock();
  {
    if (uploadVariables.count(variableName) > 0 ||
      uploadVariablesToBeRegistered.count(variableName) > 0)
    {
#if TARGET_PLATFORM == PLATFORM_WINDOWS
      sprintf_s(message, sizeof(message),
#else
      sprintf(message,
#endif
        "The variable named %s has already been registered for provision to the server.", variableName.c_str());
      variablesLock.unlock();
      throw Error(message);
    }
    else
    {
      uploadVariablesToBeRegistered[variableName] = new DWordVariable(variableName, periodicity, provider, nullptr);
    }
  }
  variablesLock.unlock();
}

void
dds::net::connector::
DdsConnector::registerQWordProvider(
  std::string variableName, QWordProvider provider, Periodicity periodicity)
{
  variablesLock.lock();
  {
    if (uploadVariables.count(variableName) > 0 ||
      uploadVariablesToBeRegistered.count(variableName) > 0)
    {
#if TARGET_PLATFORM == PLATFORM_WINDOWS
      sprintf_s(message, sizeof(message),
#else
      sprintf(message,
#endif
        "The variable named %s has already been registered for provision to the server.", variableName.c_str());
      variablesLock.unlock();
      throw Error(message);
    }
    else
    {
      uploadVariablesToBeRegistered[variableName] = new QWordVariable(variableName, periodicity, provider, nullptr);
    }
  }
  variablesLock.unlock();
}

void
dds::net::connector::
DdsConnector::registerUnsignedByteProvider(
  std::string variableName, UnsignedByteProvider provider, Periodicity periodicity)
{
  variablesLock.lock();
  {
    if (uploadVariables.count(variableName) > 0 ||
      uploadVariablesToBeRegistered.count(variableName) > 0)
    {
#if TARGET_PLATFORM == PLATFORM_WINDOWS
      sprintf_s(message, sizeof(message),
#else
      sprintf(message,
#endif
        "The variable named %s has already been registered for provision to the server.", variableName.c_str());
      variablesLock.unlock();
      throw Error(message);
    }
    else
    {
      uploadVariablesToBeRegistered[variableName] = new UnsignedByteVariable(variableName, periodicity, provider, nullptr);
    }
  }
  variablesLock.unlock();
}

void
dds::net::connector::
DdsConnector::registerUnsignedWordProvider(
  std::string variableName, UnsignedWordProvider provider, Periodicity periodicity)
{
  variablesLock.lock();
  {
    if (uploadVariables.count(variableName) > 0 ||
      uploadVariablesToBeRegistered.count(variableName) > 0)
    {
#if TARGET_PLATFORM == PLATFORM_WINDOWS
      sprintf_s(message, sizeof(message),
#else
      sprintf(message,
#endif
        "The variable named %s has already been registered for provision to the server.", variableName.c_str());
      variablesLock.unlock();
      throw Error(message);
    }
    else
    {
      uploadVariablesToBeRegistered[variableName] = new UnsignedWordVariable(variableName, periodicity, provider, nullptr);
    }
  }
  variablesLock.unlock();
}

void
dds::net::connector::
DdsConnector::registerUnsignedDWordProvider(
  std::string variableName, UnsignedDWordProvider provider, Periodicity periodicity)
{
  variablesLock.lock();
  {
    if (uploadVariables.count(variableName) > 0 ||
      uploadVariablesToBeRegistered.count(variableName) > 0)
    {
#if TARGET_PLATFORM == PLATFORM_WINDOWS
      sprintf_s(message, sizeof(message),
#else
      sprintf(message,
#endif
        "The variable named %s has already been registered for provision to the server.", variableName.c_str());
      variablesLock.unlock();
      throw Error(message);
    }
    else
    {
      uploadVariablesToBeRegistered[variableName] = new UnsignedDWordVariable(variableName, periodicity, provider, nullptr);
    }
  }
  variablesLock.unlock();
}

void
dds::net::connector::
DdsConnector::registerUnsignedQWordProvider(
  std::string variableName, UnsignedQWordProvider provider, Periodicity periodicity)
{
  variablesLock.lock();
  {
    if (uploadVariables.count(variableName) > 0 ||
      uploadVariablesToBeRegistered.count(variableName) > 0)
    {
#if TARGET_PLATFORM == PLATFORM_WINDOWS
      sprintf_s(message, sizeof(message),
#else
      sprintf(message,
#endif
        "The variable named %s has already been registered for provision to the server.", variableName.c_str());
      variablesLock.unlock();
      throw Error(message);
    }
    else
    {
      uploadVariablesToBeRegistered[variableName] = new UnsignedQWordVariable(variableName, periodicity, provider, nullptr);
    }
  }
  variablesLock.unlock();
}

void
dds::net::connector::
DdsConnector::registerSingleProvider(
  std::string variableName, SingleProvider provider, Periodicity periodicity)
{
  variablesLock.lock();
  {
    if (uploadVariables.count(variableName) > 0 ||
      uploadVariablesToBeRegistered.count(variableName) > 0)
    {
#if TARGET_PLATFORM == PLATFORM_WINDOWS
      sprintf_s(message, sizeof(message),
#else
      sprintf(message,
#endif
        "The variable named %s has already been registered for provision to the server.", variableName.c_str());
      variablesLock.unlock();
      throw Error(message);
    }
    else
    {
      uploadVariablesToBeRegistered[variableName] = new SingleVariable(variableName, periodicity, provider, nullptr);
    }
  }
  variablesLock.unlock();
}

void
dds::net::connector::
DdsConnector::registerDoubleProvider(
  std::string variableName, DoubleProvider provider, Periodicity periodicity)
{
  variablesLock.lock();
  {
    if (uploadVariables.count(variableName) > 0 ||
      uploadVariablesToBeRegistered.count(variableName) > 0)
    {
#if TARGET_PLATFORM == PLATFORM_WINDOWS
      sprintf_s(message, sizeof(message),
#else
      sprintf(message,
#endif
        "The variable named %s has already been registered for provision to the server.", variableName.c_str());
      variablesLock.unlock();
      throw Error(message);
    }
    else
    {
      uploadVariablesToBeRegistered[variableName] = new DoubleVariable(variableName, periodicity, provider, nullptr);
    }
  }
  variablesLock.unlock();
}

void
dds::net::connector::
DdsConnector::registerRawBytesProvider(
  std::string variableName, RawBytesProvider provider, Periodicity periodicity)
{
  variablesLock.lock();
  {
    if (uploadVariables.count(variableName) > 0 ||
      uploadVariablesToBeRegistered.count(variableName) > 0)
    {
#if TARGET_PLATFORM == PLATFORM_WINDOWS
      sprintf_s(message, sizeof(message),
#else
      sprintf(message,
#endif
        "The variable named %s has already been registered for provision to the server.", variableName.c_str());
      variablesLock.unlock();
      throw Error(message);
    }
    else
    {
      uploadVariablesToBeRegistered[variableName] = new RawBytesVariable(variableName, periodicity, provider, nullptr, bufferManager);
    }
  }
  variablesLock.unlock();
}

void
dds::net::connector::
DdsConnector::unregisterProvider(std::string variableName)
{
  variablesLock.lock();
  {
    if (uploadVariables.count(variableName) > 0)
    {
      uploadVariables.erase(variableName);
    }

    if (uploadVariablesToBeRegistered.count(variableName) > 0)
    {
      uploadVariablesToBeRegistered.erase(variableName);
    }
  }
  variablesLock.unlock();
}





/*************************************************************************************/
/*                                                                                   */
/* Registering:                                                                      */
/*     - Consumers                                                                   */
/*                                                                                   */
/*************************************************************************************/

void
dds::net::connector::
DdsConnector::registerStringConsumer(
  std::string variableName, StringConsumer consumer, Periodicity periodicity)
{
  variablesLock.lock();
  {
    if (downloadVariables.count(variableName) > 0 ||
      downloadVariablesToBeRegistered.count(variableName) > 0)
    {
#if TARGET_PLATFORM == PLATFORM_WINDOWS
      sprintf_s(message, sizeof(message),
#else
      sprintf(message,
#endif
        "The variable named %s has already been registered for provision from the server.", variableName.c_str());
      variablesLock.unlock();
      throw Error(message);
    }
    else
    {
      downloadVariablesToBeRegistered[
        variableName] = new StringVariable(variableName, periodicity, nullptr, consumer);
    }
  }
  variablesLock.unlock();
}

void
dds::net::connector::
DdsConnector::registerBooleanConsumer(
  std::string variableName, BooleanConsumer consumer, Periodicity periodicity)
{
  variablesLock.lock();
  {
  }
  variablesLock.unlock();
  /*
  variablesLock.lock();{}variablesLock.unlock();
          {
            if (downloadVariables.count(variableName) > 0 ||
              downloadVariablesToBeRegistered.count(variableName) > 0)
            {
              #if TARGET_PLATFORM == PLATFORM_WINDOWS
      sprintf_s(message, sizeof(message),
#else
      sprintf(message,
#endif
        "The variable named %s has already been registered for provision from the server.", variableName.c_str());
        variablesLock.unlock();
      throw Error(message);
            }
            else
            {
              downloadVariablesToBeRegistered[
                variableName] = new BooleanVariable(variableName, periodicity, nullptr, consumer);
            }
          }*/
}

void
dds::net::connector::
DdsConnector::registerByteConsumer(
  std::string variableName, ByteConsumer consumer, Periodicity periodicity)
{
  variablesLock.lock();
  {
  }
  variablesLock.unlock();
  /*
  variablesLock.lock();{}variablesLock.unlock();
          {
            if (downloadVariables.count(variableName) > 0 ||
              downloadVariablesToBeRegistered.count(variableName) > 0)
            {
              #if TARGET_PLATFORM == PLATFORM_WINDOWS
      sprintf_s(message, sizeof(message),
#else
      sprintf(message,
#endif
        "The variable named %s has already been registered for provision from the server.", variableName.c_str());
        variablesLock.unlock();
      throw Error(message);
            }
            else
            {
              downloadVariablesToBeRegistered[
                variableName] = new ByteVariable(variableName, periodicity, nullptr, consumer);
            }
          }*/
}

void
dds::net::connector::
DdsConnector::registerWordConsumer(
  std::string variableName, WordConsumer consumer, Periodicity periodicity)
{
  variablesLock.lock();
  {
  }
  variablesLock.unlock();
  /*
  variablesLock.lock();{}variablesLock.unlock();
          {
            if (downloadVariables.count(variableName) > 0 ||
              downloadVariablesToBeRegistered.count(variableName) > 0)
            {
              #if TARGET_PLATFORM == PLATFORM_WINDOWS
      sprintf_s(message, sizeof(message),
#else
      sprintf(message,
#endif
        "The variable named %s has already been registered for provision from the server.", variableName.c_str());
        variablesLock.unlock();
      throw Error(message);
            }
            else
            {
              downloadVariablesToBeRegistered[
                variableName] = new WordVariable(variableName, periodicity, nullptr, consumer);
            }
          }*/
}

void
dds::net::connector::
DdsConnector::registerDWordConsumer(
  std::string variableName, DWordConsumer consumer, Periodicity periodicity)
{
  variablesLock.lock();
  {
  }
  variablesLock.unlock();
  /*
  variablesLock.lock();{}variablesLock.unlock();
          {
            if (downloadVariables.count(variableName) > 0 ||
              downloadVariablesToBeRegistered.count(variableName) > 0)
            {
             #if TARGET_PLATFORM == PLATFORM_WINDOWS
      sprintf_s(message, sizeof(message),
#else
      sprintf(message,
#endif
        "The variable named %s has already been registered for provision from the server.", variableName.c_str());
        variablesLock.unlock();
      throw Error(message);
            }
            else
            {
              downloadVariablesToBeRegistered[
                variableName] = new DWordVariable(variableName, periodicity, nullptr, consumer);
            }
          }*/
}

void
dds::net::connector::
DdsConnector::registerQWordConsumer(
  std::string variableName, QWordConsumer consumer, Periodicity periodicity)
{
  variablesLock.lock();
  {
  }
  variablesLock.unlock();
  /*
  variablesLock.lock();{}variablesLock.unlock();
          {
            if (downloadVariables.count(variableName) > 0 ||
              downloadVariablesToBeRegistered.count(variableName) > 0)
            {
            #if TARGET_PLATFORM == PLATFORM_WINDOWS
      sprintf_s(message, sizeof(message),
#else
      sprintf(message,
#endif
        "The variable named %s has already been registered for provision from the server.", variableName.c_str());
        variablesLock.unlock();
      throw Error(message);
            }
            else
            {
              downloadVariablesToBeRegistered[
                variableName] = new QWordVariable(variableName, periodicity, nullptr, consumer);
            }
          }*/
}

void
dds::net::connector::
DdsConnector::registerUnsignedByteConsumer(
  std::string variableName, UnsignedByteConsumer consumer, Periodicity periodicity)
{
  variablesLock.lock();
  {
  }
  variablesLock.unlock();
  /*
  variablesLock.lock();{}variablesLock.unlock();
          {
            if (downloadVariables.count(variableName) > 0 ||
              downloadVariablesToBeRegistered.count(variableName) > 0)
            {
              #if TARGET_PLATFORM == PLATFORM_WINDOWS
      sprintf_s(message, sizeof(message),
#else
      sprintf(message,
#endif
        "The variable named %s has already been registered for provision from the server.", variableName.c_str());
        variablesLock.unlock();
      throw Error(message);
            }
            else
            {
              downloadVariablesToBeRegistered[
                variableName] = new UnsignedByteVariable(variableName, periodicity, nullptr, consumer);
            }
          }*/
}

void
dds::net::connector::
DdsConnector::registerUnsignedWordConsumer(
  std::string variableName, UnsignedWordConsumer consumer, Periodicity periodicity)
{
  variablesLock.lock();
  {
  }
  variablesLock.unlock();
  /*
  variablesLock.lock();{}variablesLock.unlock();
          {
            if (downloadVariables.count(variableName) > 0 ||
              downloadVariablesToBeRegistered.count(variableName) > 0)
            {
            #if TARGET_PLATFORM == PLATFORM_WINDOWS
      sprintf_s(message, sizeof(message),
#else
      sprintf(message,
#endif
        "The variable named %s has already been registered for provision from the server.", variableName.c_str());
        variablesLock.unlock();
      throw Error(message);
            }
            else
            {
              downloadVariablesToBeRegistered[
                variableName] = new UnsignedWordVariable(variableName, periodicity, nullptr, consumer);
            }
          }*/
}

void
dds::net::connector::
DdsConnector::registerUnsignedDWordConsumer(
  std::string variableName, UnsignedDWordConsumer consumer, Periodicity periodicity)
{
  variablesLock.lock();
  {
  }
  variablesLock.unlock();
  /*
  variablesLock.lock();{}variablesLock.unlock();
          {
            if (downloadVariables.count(variableName) > 0 ||
              downloadVariablesToBeRegistered.count(variableName) > 0)
            {
            #if TARGET_PLATFORM == PLATFORM_WINDOWS
      sprintf_s(message, sizeof(message),
#else
      sprintf(message,
#endif
        "The variable named %s has already been registered for provision from the server.", variableName.c_str());
        variablesLock.unlock();
      throw Error(message);
            }
            else
            {
              downloadVariablesToBeRegistered[
                variableName] = new UnsignedDWordVariable(variableName, periodicity, nullptr, consumer);
            }
          }*/
}

void
dds::net::connector::
DdsConnector::registerUnsignedQWordConsumer(
  std::string variableName, UnsignedQWordConsumer consumer, Periodicity periodicity)
{
  variablesLock.lock();
  {
  }
  variablesLock.unlock();
  /*
  variablesLock.lock();{}variablesLock.unlock();
          {
            if (downloadVariables.count(variableName) > 0 ||
              downloadVariablesToBeRegistered.count(variableName) > 0)
            {
            #if TARGET_PLATFORM == PLATFORM_WINDOWS
      sprintf_s(message, sizeof(message),
#else
      sprintf(message,
#endif
        "The variable named %s has already been registered for provision from the server.", variableName.c_str());
        variablesLock.unlock();
      throw Error(message);
            }
            else
            {
              downloadVariablesToBeRegistered[
                variableName] = new UnsignedQWordVariable(variableName, periodicity, nullptr, consumer);
            }
          }*/
}

void
dds::net::connector::
DdsConnector::registerSingleConsumer(
  std::string variableName, SingleConsumer consumer, Periodicity periodicity)
{
  variablesLock.lock();
  {
  }
  variablesLock.unlock();
  /*
  variablesLock.lock();{}variablesLock.unlock();
          {
            if (downloadVariables.count(variableName) > 0 ||
              downloadVariablesToBeRegistered.count(variableName) > 0)
            {
          #if TARGET_PLATFORM == PLATFORM_WINDOWS
      sprintf_s(message, sizeof(message),
#else
      sprintf(message,
#endif
        "The variable named %s has already been registered for provision from the server.", variableName.c_str());
        variablesLock.unlock();
      throw Error(message);
            }
            else
            {
              downloadVariablesToBeRegistered[
                variableName] = new SingleVariable(variableName, periodicity, nullptr, consumer);
            }
          }*/
}

void
dds::net::connector::
DdsConnector::registerDoubleConsumer(
  std::string variableName, DoubleConsumer consumer, Periodicity periodicity)
{
  variablesLock.lock();
  {
  }
  variablesLock.unlock();
  /*
  variablesLock.lock();{}variablesLock.unlock();
          {
            if (downloadVariables.count(variableName) > 0 ||
              downloadVariablesToBeRegistered.count(variableName) > 0)
            {
          #if TARGET_PLATFORM == PLATFORM_WINDOWS
      sprintf_s(message, sizeof(message),
#else
      sprintf(message,
#endif
        "The variable named %s has already been registered for provision from the server.", variableName.c_str());
        variablesLock.unlock();
      throw Error(message);
            }
            else
            {
              downloadVariablesToBeRegistered[
                variableName] = new DoubleVariable(variableName, periodicity, nullptr, consumer);
            }
          }*/
}

void
dds::net::connector::
DdsConnector::registerRawBytesConsumer(
  std::string variableName, RawBytesConsumer consumer, Periodicity periodicity)
{
  variablesLock.lock();
  {
  }
  variablesLock.unlock();
  /*
  variablesLock.lock();{}variablesLock.unlock();
          {
            if (downloadVariables.count(variableName) > 0 ||
              downloadVariablesToBeRegistered.count(variableName) > 0)
            {
        #if TARGET_PLATFORM == PLATFORM_WINDOWS
      sprintf_s(message, sizeof(message),
#else
      sprintf(message,
#endif
        "The variable named %s has already been registered for provision from the server.", variableName.c_str());
        variablesLock.unlock();
      throw Error(message);
            }
            else
            {
              downloadVariablesToBeRegistered[
                variableName] = new RawBytesVariable(variableName, periodicity, nullptr, consumer);
            }
          }*/
}

void
dds::net::connector::
DdsConnector::unregisterConsumer(std::string variableName)
{
  variablesLock.lock();
  {
  }
  variablesLock.unlock();
  /*
  variablesLock.lock();{}variablesLock.unlock();
          {
            if (downloadVariables.count(variableName) > 0)
            {
              downloadVariables.erase(variableName);
            }

            if (downloadVariablesToBeRegistered.count(variableName) > 0)
            {
              downloadVariablesToBeRegistered.erase(variableName);
            }
          }*/
}


