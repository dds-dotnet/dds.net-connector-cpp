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

#include <stdio.h>


using namespace dds::net::connector::_internal;

/*************************************************************************************/
/*                                                                                   */
/* Init / deinit                                                                     */
/*                                                                                   */
/*************************************************************************************/

dds::net::connector::
  DdsConnector::DdsConnector(
    std::string applicationName,
    std::string serverIPv4, ushort serverPortTCP,
    Logger* logger)
{
  this->applicationName = applicationName;
  this->serverAddressIPv4 = serverIPv4;
  this->serverPortTCP = serverPortTCP;
  this->iterationCounter = 0;
  this->bufferManager = new BufferManager();

  //- 
  //- Instantiating Logger when not provided
  //- 

  if (logger == nullptr)
  {
    this->logger = new BlankLogger();
  }
  else
  {
    this->logger = logger;
  }

  //- 
  //- Validating IP address
  //- 

  if (StringHelper::isValidIPv4Address(serverIPv4))
  {
    this->serverAddressIPv4 = StringHelper::removeSpaces(this->serverAddressIPv4);
  }
  else
  {
    char* message = this->bufferManager->get2k();

#if TARGET_PLATFORM == PLATFORM_WINDOWS
    sprintf_s(message, 2048,
#else
    sprintf(message,
#endif
      "Invalid IPv4 address: %s", serverIPv4.c_str());

    logger->error(message);

    throw Error(message);
  }

  char* message = this->bufferManager->get2k();

#if TARGET_PLATFORM == PLATFORM_WINDOWS
  sprintf_s(message, 2048,
#else
  sprintf(message,
#endif
    "Initializing connector (v%s) with Server: %s:%d, App: %s",
    DdsConnector::getLibraryVersion().c_str(),
    serverIPv4.c_str(), serverPortTCP, applicationName.c_str());

  logger->info(message);

  try
  {
    this->networkClient = new NetworkClient(this->bufferManager);
    this->dataFromServer = this->networkClient->getDataQueueFromServer();
    this->dataToServer = this->networkClient->getDataQueueToServer();
  }
  catch (std::exception& ex)
  {
#if TARGET_PLATFORM == PLATFORM_WINDOWS
    sprintf_s(message, 2048,
#else
    sprintf(message,
#endif
      "Cannot initialize network client - %s", ex.what());

    logger->error(message);

    throw ex;
  }

  this->bufferManager->free(message);

  this->dataReceiverThread = new EasyThread(dataReceptionWorker, this);
  this->periodicUpdateThread = new EasyThread(periodicUpdateWorker, this, BASE_TIME_SLOT_MSEC);

  this->networkClient->setCallbackOnConnectedWithServer(onConnectedWithServer, this);
  this->networkClient->setCallbackOnDisconnectedFromServer(onDisconnectedFromServer, this);
}

dds::net::connector::DdsConnector::
  ~DdsConnector()
{
  stop();
  delete this->bufferManager;
}

/*************************************************************************************/
/*                                                                                   */
/* Start / Stop                                                                      */
/*                                                                                   */
/*************************************************************************************/

void
  dds::net::connector::
  DdsConnector::start()
{
  dataReceiverThread->start();
  periodicUpdateThread->start();
  networkClient->connect(serverAddressIPv4, serverPortTCP);
}

void
  dds::net::connector::
  DdsConnector::stop()
{
  periodicUpdateThread->stop();

  unregisterVariablesFromServer();

  sleep(100);

  dataReceiverThread->stop();

  networkClient->disconnect();
}

/*************************************************************************************/
/*                                                                                   */
/* Info getters                                                                      */
/*                                                                                   */
/*************************************************************************************/

std::string
  dds::net::connector::
  DdsConnector::getLibraryVersion()
{
  return LIBRARY_VERSION;
}

std::string
  dds::net::connector::
  DdsConnector::getApplicationName()
{
  return this->applicationName;
}

std::string
  dds::net::connector::
  DdsConnector::getServerAddressIPv4()
{
  return this->serverAddressIPv4;
}

ushort
  dds::net::connector::
  DdsConnector::getServerPortTCP()
{
  return this->serverPortTCP;
}

/*************************************************************************************/
/*                                                                                   */
/* Periodic Updates                                                                  */
/*                                                                                   */
/*************************************************************************************/

static bool
  dds::net::connector::
  periodicUpdateWorker(void* connector)
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

void
  dds::net::connector::
  DdsConnector::doPeriodicUpdate(Periodicity periodicity)
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
                            v.Value.Periodicity == Periodicity.ON_CHANGE)
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

/*************************************************************************************/
/*                                                                                   */
/* Communication with the Server                                                     */
/*                                                                                   */
/*************************************************************************************/

void
  dds::net::connector::
  DdsConnector::registerAwaitingVariablesWithServer()
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

void
  dds::net::connector::
  DdsConnector::unregisterVariablesFromServer()
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

void
  dds::net::connector::
  DdsConnector::sendUpdatedValuesToServer(
    std::list<_internal::variables::BaseVariable*>& vars)
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

/*************************************************************************************/
/*                                                                                   */
/* Connection Events                                                                 */
/*                                                                                   */
/*************************************************************************************/

static void
  dds::net::connector::
  onConnectedWithServer(void* connector)
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

static void
  dds::net::connector::
  onDisconnectedFromServer(void* connector)
{
  /*
  variablesLock.lock();
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

/*************************************************************************************/
/*                                                                                   */
/* Data Reception                                                                    */
/*                                                                                   */
/*************************************************************************************/

static bool
  dds::net::connector::
  dataReceptionWorker(void* connector)
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
