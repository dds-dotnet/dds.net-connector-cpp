#include "inc/ddsconnector.h"

#include "inc/logger.h"

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
  catch (std::exception ex)
  {
    std::string errorMessage = "Cannot initialize network client - ";
    errorMessage = errorMessage + ex.what();

    logger->error(errorMessage.c_str());

    throw ex;
  }

  this->dataReceiverThread = new EasyThread(dataReceptionWorker, this);
  this->periodicUpdateThread = new EasyThread(periodicUpdateWorker, this, BASE_TIME_SLOT_MS);

  this->networkClient->setCallbackOnConnectedWithServer(onConnectedWithServer);
  this->networkClient->setCallbackOnDisconnectedFromServer(onDisconnectedFromServer);
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


