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
  /*
  variablesLock.lock();
          {
            if (uploadVariables.ContainsKey(variableName) ||
              uploadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision to the server.");
            }
            else
            {
              uploadVariablesToBeRegistered.Add(variableName, new StringVariable(variableName, periodicity, provider));
            }
          }*/
}

void
dds::net::connector::
DdsConnector::registerBooleanProvider(
  std::string variableName, BooleanProvider provider, Periodicity periodicity)
{
  /*
  variablesLock.lock();
          {
            if (uploadVariables.ContainsKey(variableName) ||
              uploadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision to the server.");
            }
            else
            {
              uploadVariablesToBeRegistered.Add(variableName, new BooleanVariable(variableName, periodicity, provider));
            }
          }*/
}

void
dds::net::connector::
DdsConnector::registerByteProvider(
  std::string variableName, ByteProvider provider, Periodicity periodicity)
{
  /*
  variablesLock.lock();
          {
            if (uploadVariables.ContainsKey(variableName) ||
              uploadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision to the server.");
            }
            else
            {
              uploadVariablesToBeRegistered.Add(variableName, new ByteVariable(variableName, periodicity, provider));
            }
          }*/
}

void
dds::net::connector::
DdsConnector::registerWordProvider(
  std::string variableName, WordProvider provider, Periodicity periodicity)
{
  /*variablesLock.lock();
          {
            if (uploadVariables.ContainsKey(variableName) ||
              uploadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision to the server.");
            }
            else
            {
              uploadVariablesToBeRegistered.Add(variableName, new WordVariable(variableName, periodicity, provider));
            }
          }*/
}

void
dds::net::connector::
DdsConnector::registerDWordProvider(
  std::string variableName, DWordProvider provider, Periodicity periodicity)
{
  /*
  variablesLock.lock();
          {
            if (uploadVariables.ContainsKey(variableName) ||
              uploadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision to the server.");
            }
            else
            {
              uploadVariablesToBeRegistered.Add(variableName, new DWordVariable(variableName, periodicity, provider));
            }
          }*/
}

void
dds::net::connector::
DdsConnector::registerQWordProvider(
  std::string variableName, QWordProvider provider, Periodicity periodicity)
{
  /*
  variablesLock.lock();
          {
            if (uploadVariables.ContainsKey(variableName) ||
              uploadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision to the server.");
            }
            else
            {
              uploadVariablesToBeRegistered.Add(variableName, new QWordVariable(variableName, periodicity, provider));
            }
          }*/
}

void
dds::net::connector::
DdsConnector::registerUnsignedByteProvider(
  std::string variableName, UnsignedByteProvider provider, Periodicity periodicity)
{
  /*
  variablesLock.lock();
          {
            if (uploadVariables.ContainsKey(variableName) ||
              uploadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision to the server.");
            }
            else
            {
              uploadVariablesToBeRegistered.Add(variableName, new UnsignedByteVariable(variableName, periodicity, provider));
            }
          }*/
}

void
dds::net::connector::
DdsConnector::registerUnsignedWordProvider(
  std::string variableName, UnsignedWordProvider provider, Periodicity periodicity)
{
  /*
  variablesLock.lock();
          {
            if (uploadVariables.ContainsKey(variableName) ||
              uploadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision to the server.");
            }
            else
            {
              uploadVariablesToBeRegistered.Add(variableName, new UnsignedWordVariable(variableName, periodicity, provider));
            }
          }*/
}

void
dds::net::connector::
DdsConnector::registerUnsignedDWordProvider(
  std::string variableName, UnsignedDWordProvider provider, Periodicity periodicity)
{
  /*
  variablesLock.lock();
          {
            if (uploadVariables.ContainsKey(variableName) ||
              uploadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision to the server.");
            }
            else
            {
              uploadVariablesToBeRegistered.Add(variableName, new UnsignedDWordVariable(variableName, periodicity, provider));
            }
          }*/
}

void
dds::net::connector::
DdsConnector::registerUnsignedQWordProvider(
  std::string variableName, UnsignedQWordProvider provider, Periodicity periodicity)
{
  /*
  variablesLock.lock();
          {
            if (uploadVariables.ContainsKey(variableName) ||
              uploadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision to the server.");
            }
            else
            {
              uploadVariablesToBeRegistered.Add(variableName, new UnsignedQWordVariable(variableName, periodicity, provider));
            }
          }*/
}

void
dds::net::connector::
DdsConnector::registerSingleProvider(
  std::string variableName, SingleProvider provider, Periodicity periodicity)
{
  /*
  variablesLock.lock();
          {
            if (uploadVariables.ContainsKey(variableName) ||
              uploadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision to the server.");
            }
            else
            {
              uploadVariablesToBeRegistered.Add(variableName, new SingleVariable(variableName, periodicity, provider));
            }
          }*/
}

void
dds::net::connector::
DdsConnector::registerDoubleProvider(
  std::string variableName, DoubleProvider provider, Periodicity periodicity)
{
  /*
  variablesLock.lock();
          {
            if (uploadVariables.ContainsKey(variableName) ||
              uploadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision to the server.");
            }
            else
            {
              uploadVariablesToBeRegistered.Add(variableName, new DoubleVariable(variableName, periodicity, provider));
            }
          }*/
}

void
dds::net::connector::
DdsConnector::registerRawBytesProvider(
  std::string variableName, RawBytesProvider provider, Periodicity periodicity)
{
  /*
  variablesLock.lock();
          {
            if (uploadVariables.ContainsKey(variableName) ||
              uploadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision to the server.");
            }
            else
            {
              uploadVariablesToBeRegistered.Add(variableName, new RawBytesVariable(variableName, periodicity, provider));
            }
          }*/
}

void
dds::net::connector::
DdsConnector::unregisterProvider(std::string variableName)
{
  /*
  variablesLock.lock();
          {
            if (uploadVariables.ContainsKey(variableName))
            {
              uploadVariables.Remove(variableName);
            }

            if (uploadVariablesToBeRegistered.ContainsKey(variableName))
            {
              uploadVariablesToBeRegistered.Remove(variableName);
            }
          }*/
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
  /*
  variablesLock.lock();
          {
            if (downloadVariables.ContainsKey(variableName) ||
              downloadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision from the server.");
            }
            else
            {
              downloadVariablesToBeRegistered.Add(
                variableName, new StringVariable(variableName, periodicity, null!, consumer));
            }
          }*/
}

void
dds::net::connector::
DdsConnector::registerBooleanConsumer(
  std::string variableName, BooleanConsumer consumer, Periodicity periodicity)
{
  /*
  variablesLock.lock();
          {
            if (downloadVariables.ContainsKey(variableName) ||
              downloadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision from the server.");
            }
            else
            {
              downloadVariablesToBeRegistered.Add(
                variableName, new BooleanVariable(variableName, periodicity, null!, consumer));
            }
          }*/
}

void
dds::net::connector::
DdsConnector::registerByteConsumer(
  std::string variableName, ByteConsumer consumer, Periodicity periodicity)
{
  /*
  variablesLock.lock();
          {
            if (downloadVariables.ContainsKey(variableName) ||
              downloadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision from the server.");
            }
            else
            {
              downloadVariablesToBeRegistered.Add(
                variableName, new ByteVariable(variableName, periodicity, null!, consumer));
            }
          }*/
}

void
dds::net::connector::
DdsConnector::registerWordConsumer(
  std::string variableName, WordConsumer consumer, Periodicity periodicity)
{
  /*
  variablesLock.lock();
          {
            if (downloadVariables.ContainsKey(variableName) ||
              downloadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision from the server.");
            }
            else
            {
              downloadVariablesToBeRegistered.Add(
                variableName, new WordVariable(variableName, periodicity, null!, consumer));
            }
          }*/
}

void
dds::net::connector::
DdsConnector::registerDWordConsumer(
  std::string variableName, DWordConsumer consumer, Periodicity periodicity)
{
  /*
  variablesLock.lock();
          {
            if (downloadVariables.ContainsKey(variableName) ||
              downloadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision from the server.");
            }
            else
            {
              downloadVariablesToBeRegistered.Add(
                variableName, new DWordVariable(variableName, periodicity, null!, consumer));
            }
          }*/
}

void
dds::net::connector::
DdsConnector::registerQWordConsumer(
  std::string variableName, QWordConsumer consumer, Periodicity periodicity)
{
  /*
  variablesLock.lock();
          {
            if (downloadVariables.ContainsKey(variableName) ||
              downloadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision from the server.");
            }
            else
            {
              downloadVariablesToBeRegistered.Add(
                variableName, new QWordVariable(variableName, periodicity, null!, consumer));
            }
          }*/
}

void
dds::net::connector::
DdsConnector::registerUnsignedByteConsumer(
  std::string variableName, UnsignedByteConsumer consumer, Periodicity periodicity)
{
  /*
  variablesLock.lock();
          {
            if (downloadVariables.ContainsKey(variableName) ||
              downloadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision from the server.");
            }
            else
            {
              downloadVariablesToBeRegistered.Add(
                variableName, new UnsignedByteVariable(variableName, periodicity, null!, consumer));
            }
          }*/
}

void
dds::net::connector::
DdsConnector::registerUnsignedWordConsumer(
  std::string variableName, UnsignedWordConsumer consumer, Periodicity periodicity)
{
  /*
  variablesLock.lock();
          {
            if (downloadVariables.ContainsKey(variableName) ||
              downloadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision from the server.");
            }
            else
            {
              downloadVariablesToBeRegistered.Add(
                variableName, new UnsignedWordVariable(variableName, periodicity, null!, consumer));
            }
          }*/
}

void
dds::net::connector::
DdsConnector::registerUnsignedDWordConsumer(
  std::string variableName, UnsignedDWordConsumer consumer, Periodicity periodicity)
{
  /*
  variablesLock.lock();
          {
            if (downloadVariables.ContainsKey(variableName) ||
              downloadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision from the server.");
            }
            else
            {
              downloadVariablesToBeRegistered.Add(
                variableName, new UnsignedDWordVariable(variableName, periodicity, null!, consumer));
            }
          }*/
}

void
dds::net::connector::
DdsConnector::registerUnsignedQWordConsumer(
  std::string variableName, UnsignedQWordConsumer consumer, Periodicity periodicity)
{
  /*
  variablesLock.lock();
          {
            if (downloadVariables.ContainsKey(variableName) ||
              downloadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision from the server.");
            }
            else
            {
              downloadVariablesToBeRegistered.Add(
                variableName, new UnsignedQWordVariable(variableName, periodicity, null!, consumer));
            }
          }*/
}

void
dds::net::connector::
DdsConnector::registerSingleConsumer(
  std::string variableName, SingleConsumer consumer, Periodicity periodicity)
{
  /*
  variablesLock.lock();
          {
            if (downloadVariables.ContainsKey(variableName) ||
              downloadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision from the server.");
            }
            else
            {
              downloadVariablesToBeRegistered.Add(
                variableName, new SingleVariable(variableName, periodicity, null!, consumer));
            }
          }*/
}

void
dds::net::connector::
DdsConnector::registerDoubleConsumer(
  std::string variableName, DoubleConsumer consumer, Periodicity periodicity)
{
  /*
  variablesLock.lock();
          {
            if (downloadVariables.ContainsKey(variableName) ||
              downloadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision from the server.");
            }
            else
            {
              downloadVariablesToBeRegistered.Add(
                variableName, new DoubleVariable(variableName, periodicity, null!, consumer));
            }
          }*/
}

void
dds::net::connector::
DdsConnector::registerRawBytesConsumer(
  std::string variableName, RawBytesConsumer consumer, Periodicity periodicity)
{
  /*
  variablesLock.lock();
          {
            if (downloadVariables.ContainsKey(variableName) ||
              downloadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision from the server.");
            }
            else
            {
              downloadVariablesToBeRegistered.Add(
                variableName, new RawBytesVariable(variableName, periodicity, null!, consumer));
            }
          }*/
}

void
dds::net::connector::
DdsConnector::unregisterConsumer(std::string variableName)
{
  /*
  variablesLock.lock();
          {
            if (downloadVariables.ContainsKey(variableName))
            {
              downloadVariables.Remove(variableName);
            }

            if (downloadVariablesToBeRegistered.ContainsKey(variableName))
            {
              downloadVariablesToBeRegistered.Remove(variableName);
            }
          }*/
}


