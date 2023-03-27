#include "inc/ddsconnector.h"

#include "inc/logger.h"

#include "src/internal/inc/macros.h"
#include "src/internal/inc/string_helper.h"
#include "src/internal/inc/threaded_network_client.h"
#include "src/internal/inc/network_client.h"
#include "src/internal/inc/easy_thread.h"

#include <exception>


using namespace dds::net::connector::_internal;


dds::net::connector::DdsConnector::DdsConnector(
  std::string applicationName, std::string serverIPv4, ushort serverPortTCP, Logger* logger)
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
  this->periodicUpdateThread = new EasyThread(periodicUpdateWorker, this, BASE_TIME_SLOT_MS);

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

  connector.DoPeriodicUpdate(Periodicity.Highest);

  if (connector.iterationCounter % 2 == 0) connector.DoPeriodicUpdate(Periodicity.High);
  if (connector.iterationCounter % 4 == 0) connector.DoPeriodicUpdate(Periodicity.Normal);
  if (connector.iterationCounter % 8 == 0) connector.DoPeriodicUpdate(Periodicity.Low);

  if (connector.iterationCounter % 16 == 0)
  {
    connector.DoPeriodicUpdate(Periodicity.Lowest);
    connector.iterationCounter = 0;
  }*/

  return true;
}
