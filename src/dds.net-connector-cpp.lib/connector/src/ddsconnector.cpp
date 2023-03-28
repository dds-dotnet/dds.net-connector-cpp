#include "inc/ddsconnector.h"

#include "inc/logger.h"

#include "src/internal/inc/macros.h"
#include "src/internal/inc/string_helper.h"
#include "src/internal/inc/threaded_network_client.h"
#include "src/internal/inc/network_client.h"
#include "src/internal/inc/easy_thread.h"

#include "src/internal/variable/base_variable.h"

#include <exception>


using namespace dds::net::connector::_internal;


dds::net::connector::DdsConnector::DdsConnector(
  std::string& applicationName,
  std::string& serverIPv4, ushort serverPortTCP,
  Logger* logger)
{
  this->applicationName = applicationName;
  this->serverAddressIPv4 = serverIPv4;
  this->serverPortTCP = serverPortTCP;
  this->iterationCounter = 0;

  if (logger == nullptr)
  {
    this->logger = new BlankLogger();
  }
  else
  {
    this->logger = logger;
  }

  if (StringHelper::isValidIPv4Address(serverIPv4))
  {
    this->serverAddressIPv4 = StringHelper::removeSpaces(this->serverAddressIPv4);
  }

  logger->info("Initializing connector");

  try
  {
    this->networkClient = new NetworkClient();
    this->dataFromServer = this->networkClient->getDataQueueFromServer();
    this->dataToServer = this->networkClient->getDataQueueToServer();
  }
  catch (std::exception& ex)
  {
    std::string errorMessage = "Cannot initialize network client - ";
    errorMessage = errorMessage + ex.what();

    logger->error(errorMessage.c_str());

    throw ex;
  }

  this->dataReceiverThread = new EasyThread(dataReceptionWorker, this);
  this->periodicUpdateThread = new EasyThread(periodicUpdateWorker, this, BASE_TIME_SLOT_MSEC);

  this->networkClient->setCallbackOnConnectedWithServer(onConnectedWithServer, this);
  this->networkClient->setCallbackOnDisconnectedFromServer(onDisconnectedFromServer, this);
}

void dds::net::connector::DdsConnector::start()
{
  dataReceiverThread->start();
  periodicUpdateThread->start();
  networkClient->connect(serverAddressIPv4, serverPortTCP);
}

void dds::net::connector::DdsConnector::stop()
{
  periodicUpdateThread->stop();

  unregisterVariablesFromServer();

  sleep(100);

  dataReceiverThread->stop();

  networkClient->disconnect();
}

std::string dds::net::connector::DdsConnector::getLibraryVersion()
{
  return LIBRARY_VERSION;
}

std::string dds::net::connector::DdsConnector::getApplicationName()
{
  return this->applicationName;
}

std::string dds::net::connector::DdsConnector::getServerAddressIPv4()
{
  return this->serverAddressIPv4;
}

ushort dds::net::connector::DdsConnector::getServerPortTCP()
{
  return this->serverPortTCP;
}

void dds::net::connector::DdsConnector::registerStringProvider(std::string variableName, StringProvider provider, Periodicity periodicity)
{
  /*
  lock(variablesMutex)
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

void dds::net::connector::DdsConnector::registerBooleanProvider(std::string variableName, BooleanProvider provider, Periodicity periodicity)
{
  /*
  lock(variablesMutex)
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

void dds::net::connector::DdsConnector::registerByteProvider(std::string variableName, ByteProvider provider, Periodicity periodicity)
{
  /*
  lock(variablesMutex)
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

void dds::net::connector::DdsConnector::registerWordProvider(std::string variableName, WordProvider provider, Periodicity periodicity)
{
  /*lock(variablesMutex)
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

void dds::net::connector::DdsConnector::registerDWordProvider(std::string variableName, DWordProvider provider, Periodicity periodicity)
{
  /*
  lock(variablesMutex)
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

void dds::net::connector::DdsConnector::registerQWordProvider(std::string variableName, QWordProvider provider, Periodicity periodicity)
{
  /*
  lock(variablesMutex)
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

void dds::net::connector::DdsConnector::registerUnsignedByteProvider(std::string variableName, UnsignedByteProvider provider, Periodicity periodicity)
{
  /*
  lock(variablesMutex)
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

void dds::net::connector::DdsConnector::registerUnsignedWordProvider(std::string variableName, UnsignedWordProvider provider, Periodicity periodicity)
{
  /*
  lock(variablesMutex)
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

void dds::net::connector::DdsConnector::registerUnsignedDWordProvider(std::string variableName, UnsignedDWordProvider provider, Periodicity periodicity)
{
  /*
  lock(variablesMutex)
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

void dds::net::connector::DdsConnector::registerUnsignedQWordProvider(std::string variableName, UnsignedQWordProvider provider, Periodicity periodicity)
{
  /*
  lock(variablesMutex)
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

void dds::net::connector::DdsConnector::registerSingleProvider(std::string variableName, SingleProvider provider, Periodicity periodicity)
{
  /*
  lock(variablesMutex)
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

void dds::net::connector::DdsConnector::registerDoubleProvider(std::string variableName, DoubleProvider provider, Periodicity periodicity)
{
  /*
  lock(variablesMutex)
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

void dds::net::connector::DdsConnector::registerRawBytesProvider(std::string variableName, RawBytesProvider provider, Periodicity periodicity)
{
  /*
  lock(variablesMutex)
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

void dds::net::connector::DdsConnector::unregisterProvider(std::string variableName)
{
  /*
  lock(variablesMutex)
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

void dds::net::connector::DdsConnector::registerStringConsumer(std::string variableName, StringConsumer consumer, Periodicity periodicity)
{
  /*
  lock(variablesMutex)
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

void dds::net::connector::DdsConnector::registerBooleanConsumer(std::string variableName, BooleanConsumer consumer, Periodicity periodicity)
{
  /*
  lock(variablesMutex)
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

void dds::net::connector::DdsConnector::registerByteConsumer(std::string variableName, ByteConsumer consumer, Periodicity periodicity)
{
  /*
  lock(variablesMutex)
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

void dds::net::connector::DdsConnector::registerWordConsumer(std::string variableName, WordConsumer consumer, Periodicity periodicity)
{
  /*
  lock(variablesMutex)
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

void dds::net::connector::DdsConnector::registerDWordConsumer(std::string variableName, DWordConsumer consumer, Periodicity periodicity)
{
  /*
  lock(variablesMutex)
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

void dds::net::connector::DdsConnector::registerQWordConsumer(std::string variableName, QWordConsumer consumer, Periodicity periodicity)
{
  /*
  lock(variablesMutex)
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

void dds::net::connector::DdsConnector::registerUnsignedByteConsumer(std::string variableName, UnsignedByteConsumer consumer, Periodicity periodicity)
{
  /*
  lock(variablesMutex)
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

void dds::net::connector::DdsConnector::registerUnsignedWordConsumer(std::string variableName, UnsignedWordConsumer consumer, Periodicity periodicity)
{
  /*
  lock(variablesMutex)
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

void dds::net::connector::DdsConnector::registerUnsignedDWordConsumer(std::string variableName, UnsignedDWordConsumer consumer, Periodicity periodicity)
{
  /*
  lock(variablesMutex)
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

void dds::net::connector::DdsConnector::registerUnsignedQWordConsumer(std::string variableName, UnsignedQWordConsumer consumer, Periodicity periodicity)
{
  /*
  lock(variablesMutex)
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

void dds::net::connector::DdsConnector::registerSingleConsumer(std::string variableName, SingleConsumer consumer, Periodicity periodicity)
{
  /*
  lock(variablesMutex)
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

void dds::net::connector::DdsConnector::registerDoubleConsumer(std::string variableName, DoubleConsumer consumer, Periodicity periodicity)
{
  /*
  lock(variablesMutex)
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

void dds::net::connector::DdsConnector::registerRawBytesConsumer(std::string variableName, RawBytesConsumer consumer, Periodicity periodicity)
{
  /*
  lock(variablesMutex)
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

void dds::net::connector::DdsConnector::unregisterConsumer(std::string variableName)
{
  /*
  lock(variablesMutex)
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

void dds::net::connector::DdsConnector::doPeriodicUpdate(Periodicity periodicity)
{
  /*
  if (periodicity == Periodicity.Normal)
            {
                RegisterAwaitingVariablesWithServer();
            }

            lock (variablesMutex)
            {
                List<BaseVariable> refreshed = new();

                if (periodicity == Periodicity.High)
                {
                    foreach (KeyValuePair<string, BaseVariable> v in uploadVariables)
                    {
                        if (v.Value.Periodicity == periodicity ||
                            v.Value.Periodicity == Periodicity.OnChange)
                        {
                            if (v.Value.RefreshValue())
                            {
                                refreshed.Add(v.Value);
                            }
                        }
                    }
                }
                else
                {
                    foreach (KeyValuePair<string, BaseVariable> v in uploadVariables)
                    {
                        if (v.Value.Periodicity == periodicity)
                        {
                            if (v.Value.RefreshValue())
                            {
                                refreshed.Add(v.Value);
                            }
                        }
                    }
                }

                SendUpdatedValuesToServer(refreshed);
            }*/
}

void dds::net::connector::DdsConnector::registerAwaitingVariablesWithServer()
{
  /*
  lock (variablesMutex)
            {
                int sizeRequired = 0;

                foreach (KeyValuePair<string, BaseVariable> v in uploadVariablesToBeRegistered)
                {
                    sizeRequired +=
                        2 + Encoding.Unicode.GetBytes(v.Key).Length + // Variable name
                        Periodicity.Normal.GetSizeOnBuffer() +        // Periodicity
                        1 +                                           // Provider/Consumer
                        1;                                            // Register/Unregister
                }

                foreach (KeyValuePair<string, BaseVariable> v in downloadVariablesToBeRegistered)
                {
                    sizeRequired +=
                        2 + Encoding.Unicode.GetBytes(v.Key).Length + // Variable name
                        Periodicity.Normal.GetSizeOnBuffer() +        // Periodicity
                        1 +                                           // Provider/Consumer
                        1;                                            // Register/Unregister
                }

                if (sizeRequired > 0)
                {
                    sizeRequired += EncDecMessageHeader.GetMessageHeaderSizeOnBuffer();
                    sizeRequired += PacketId.VariablesRegistration.GetSizeOnBuffer();

                    byte[] buffer = new byte[sizeRequired];
                    int bufferOffset = 0;

                    buffer.WriteMessageHeader(ref bufferOffset, buffer.Length - EncDecMessageHeader.GetMessageHeaderSizeOnBuffer());
                    buffer.WritePacketId(ref bufferOffset, PacketId.VariablesRegistration);

                    foreach (KeyValuePair<string, BaseVariable> v in uploadVariablesToBeRegistered)
                    {
                        buffer.WriteString(ref bufferOffset, v.Key);
                        buffer.WritePeriodicity(ref bufferOffset, v.Value.Periodicity);
                        buffer.WriteBoolean(ref bufferOffset, true); // Client is provider of data
                        buffer.WriteBoolean(ref bufferOffset, true); // Do register
                    }

                    foreach (KeyValuePair<string, BaseVariable> v in downloadVariablesToBeRegistered)
                    {
                        buffer.WriteString(ref bufferOffset, v.Key);
                        buffer.WritePeriodicity(ref bufferOffset, v.Value.Periodicity);
                        buffer.WriteBoolean(ref bufferOffset, false); // Client is consumer of data
                        buffer.WriteBoolean(ref bufferOffset, true); // Do register
                    }

                    DataToServer.Enqueue(new PacketToServer(buffer, bufferOffset));
                }
            }*/
}

void dds::net::connector::DdsConnector::unregisterVariablesFromServer()
{
  /*
  lock (variablesMutex)
            {
                int sizeRequired = 0;

                foreach (KeyValuePair<string, BaseVariable> v in uploadVariables)
                {
                    sizeRequired +=
                        2 + Encoding.Unicode.GetBytes(v.Key).Length + // Variable name
                        Periodicity.Normal.GetSizeOnBuffer() +        // Periodicity
                        1 +                                           // Provider/Consumer
                        1;                                            // Register/Unregister
                }

                foreach (KeyValuePair<string, BaseVariable> v in downloadVariables)
                {
                    sizeRequired +=
                        2 + Encoding.Unicode.GetBytes(v.Key).Length + // Variable name
                        Periodicity.Normal.GetSizeOnBuffer() +        // Periodicity
                        1 +                                           // Provider/Consumer
                        1;                                            // Register/Unregister
                }

                if (sizeRequired > 0)
                {
                    sizeRequired += EncDecMessageHeader.GetMessageHeaderSizeOnBuffer();
                    sizeRequired += PacketId.VariablesRegistration.GetSizeOnBuffer();

                    byte[] buffer = new byte[sizeRequired];
                    int bufferOffset = 0;

                    buffer.WriteMessageHeader(ref bufferOffset, buffer.Length - EncDecMessageHeader.GetMessageHeaderSizeOnBuffer());
                    buffer.WritePacketId(ref bufferOffset, PacketId.VariablesRegistration);

                    foreach (KeyValuePair<string, BaseVariable> v in uploadVariables)
                    {
                        buffer.WriteString(ref bufferOffset, v.Key);
                        buffer.WritePeriodicity(ref bufferOffset, v.Value.Periodicity);
                        buffer.WriteBoolean(ref bufferOffset, true); // Client is provider of data
                        buffer.WriteBoolean(ref bufferOffset, false); // Do register
                    }

                    foreach (KeyValuePair<string, BaseVariable> v in downloadVariables)
                    {
                        buffer.WriteString(ref bufferOffset, v.Key);
                        buffer.WritePeriodicity(ref bufferOffset, v.Value.Periodicity);
                        buffer.WriteBoolean(ref bufferOffset, false); // Client is consumer of data
                        buffer.WriteBoolean(ref bufferOffset, false); // Do register
                    }

                    DataToServer.Enqueue(new PacketToServer(buffer, bufferOffset));
                }
            }*/
}

void dds::net::connector::DdsConnector::sendUpdatedValuesToServer(std::list<_internal::variable::BaseVariable*>& vars)
{
  /*
  int sizeRequired = 0;

            foreach (BaseVariable v in vals)
            {
                sizeRequired += v.GetSizeOnBuffer();
            }

            if (sizeRequired > 0)
            {
                sizeRequired += EncDecMessageHeader.GetMessageHeaderSizeOnBuffer();
                sizeRequired += PacketId.VariablesUpdateAtServer.GetSizeOnBuffer();

                byte[] buffer = new byte[sizeRequired];
                int bufferOffset = 0;

                buffer.WriteMessageHeader(ref bufferOffset, buffer.Length - EncDecMessageHeader.GetMessageHeaderSizeOnBuffer());
                buffer.WritePacketId(ref bufferOffset, PacketId.VariablesUpdateAtServer);

                foreach (BaseVariable v in vals)
                {
                    v.WriteOnBuffer(ref buffer, ref bufferOffset);
                }

                DataToServer.Enqueue(new PacketToServer(buffer, bufferOffset));
            }*/
}

static void dds::net::connector::onConnectedWithServer(void* connector)
{
  /*
  dds::net::connector::DdsConnector::DdsConnector* conn = (dds::net::connector::DdsConnector*)connector;
  byte[] handshake = new byte[
    EncDecMessageHeader.GetMessageHeaderSizeOnBuffer() +
      PacketId.HandShake.GetSizeOnBuffer() +
      2 + Encoding.Unicode.GetBytes(ApplicationName).Length +
      2 + Encoding.Unicode.GetBytes(LibraryVersion).Length];
  int offset = 0;

  handshake.WriteMessageHeader(ref offset, handshake.Length - EncDecMessageHeader.GetMessageHeaderSizeOnBuffer());
  handshake.WritePacketId(ref offset, PacketId.HandShake);
  handshake.WriteString(ref offset, ApplicationName);
  handshake.WriteString(ref offset, LibraryVersion);

  DataToServer.Enqueue(new(handshake, offset));*/
}

static void dds::net::connector::onDisconnectedFromServer(void* connector)
{
  /*
  lock(variablesMutex)
  {
    foreach(KeyValuePair<string, BaseVariable> v in uploadVariables)
    {
      v.Value.Reset();
      uploadVariablesToBeRegistered.Add(v.Key, v.Value);
    }

    foreach(KeyValuePair<string, BaseVariable> v in downloadVariables)
    {
      v.Value.Reset();
      downloadVariablesToBeRegistered.Add(v.Key, v.Value);
    }

    uploadVariables.Clear();
    downloadVariables.Clear();
  }
  */
}

static bool dds::net::connector::dataReceptionWorker(void* connector)
{
  /*
  bool doneAnything = false;

  while (connector.DataFromServer.CanDequeue())
  {
    doneAnything = true;

    PacketPreprocessor.AddData(connector.DataFromServer.Dequeue());

    while (true)
    {
      byte[] message = PacketPreprocessor.GetSingleMessage();

      if (message != null)
      {
        connector.ParsePacket(message);
      }
      else
      {
        break;
      }
    }
  }

  return doneAnything;
  */

  return false;
}

static bool dds::net::connector::periodicUpdateWorker(void* connector)
{
  /*
  connector.iterationCounter++;

  connector.doPeriodicUpdate(Periodicity.Highest);

  if (connector.iterationCounter % 2 == 0) connector.doPeriodicUpdate(Periodicity.High);
  if (connector.iterationCounter % 4 == 0) connector.doPeriodicUpdate(Periodicity.Normal);
  if (connector.iterationCounter % 8 == 0) connector.doPeriodicUpdate(Periodicity.Low);

  if (connector.iterationCounter % 16 == 0)
  {
    connector.doPeriodicUpdate(Periodicity.Lowest);
    connector.iterationCounter = 0;
  }*/

  return true;
}
