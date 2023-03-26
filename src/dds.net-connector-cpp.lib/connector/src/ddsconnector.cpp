#include "inc/ddsconnector.h"

#include "inc/logger.h"

#include <exception>


dds::net::connector::DdsConnector::DdsConnector(
  std::string applicationName, std::string serverIPv4, ushort serverPortTCP, Logger* logger)
{
  this->applicationName = applicationName;
  this->serverAddressIPv4 = serverIPv4;
  this->serverPortTCP = serverPortTCP;

  if (logger == nullptr)
  {
    this->logger = new BlankLogger();
  }
  else
  {
    this->logger = logger;
  }

  if (serverIPv4.IsValidIPv4Address())
  {
    ServerAddressIPv4 = ServerAddressIPv4.RemoveSpaces();
  }

  Logger.Info(
    $"Initializing connector version {Settings.CONNECTOR_VERSION} " +
    $"with target server @{ServerAddressIPv4}:{ServerPortTCP}");

  try
  {
    NetworkClient = new NetworkClient();
    DataFromServer = NetworkClient.GetDataQueueFromServer();
    DataToServer = NetworkClient.GetDataQueueToServer();
  }
  catch (Exception ex)
  {
    string errorMessage = $"Cannot initialize network client - {ex.Message}";

    Logger.Error(errorMessage);

    throw new Exception(errorMessage);
  }

  dataReceiverThread = new(DataReceptionWorker, this);
  periodicUpdateThread = new(PeriodicUpdateWorker, this, Settings.BASE_TIME_SLOT_MS);

  NetworkClient.ConnectedWithServer += OnConnectedWithServer;
  NetworkClient.DisconnectedFromServer += OnDisconnectedFromServer;
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


