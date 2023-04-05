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

bool
  dds::net::connector::
  periodicUpdateWorker(void* connector)
{
  DdsConnector* conn = (DdsConnector*)connector;

  conn->iterationCounter++;

  conn->doPeriodicUpdate(HIGHEST);

  if (conn->iterationCounter % 2 == 0) conn->doPeriodicUpdate(HIGH);
  if (conn->iterationCounter % 4 == 0) conn->doPeriodicUpdate(NORMAL);
  if (conn->iterationCounter % 8 == 0) conn->doPeriodicUpdate(LOW);

  if (conn->iterationCounter % 16 == 0)
  {
    conn->doPeriodicUpdate(LOWEST);
    conn->iterationCounter = 0;
  }

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

