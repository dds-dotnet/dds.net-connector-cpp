#include "inc/ddsconnector.h"

#include "inc/error.h"

#include "src/internal/inc/macros.h"
#include "src/internal/inc/internal_types.h"
#include "src/internal/inc/string_helper.h"
#include "src/internal/inc/buffer_manager.h"
#include "src/internal/inc/threaded_network_client.h"
#include "src/internal/inc/network_client.h"
#include "src/internal/inc/easy_thread.h"

#include "src/internal/inc/sync_queue_reader.h"
#include "src/internal/inc/sync_queue_writer.h"
#include "src/internal/inc/packet_to_server.h"
#include "src/internal/inc/packet_from_server.h"
#include "src/internal/inc/packet_preprocessor.h"

#include "src/internal/inc/variables/base_variable.h"
#include "src/internal/inc/variables/enc_dec_header.h"
#include "src/internal/inc/variables/enc_dec_primitive.h"


using namespace dds::net::connector::_internal::variables;



/*************************************************************************************/
/*                                                                                   */
/* Communication with the Server                                                     */
/*                                                                                   */
/*************************************************************************************/

void
  dds::net::connector::
  DdsConnector::registerAwaitingVariablesWithServer()
{
  variablesLock.lock();
  {
    int sizeRequired = 0;

    for (auto& v : uploadVariablesToBeRegistered)
    {
      sizeRequired +=
        EncDecPrimitive::getStringSizeOnBuffer(v.second->name) + // Variable name
        EncDecHeader::PERIODICITY_SIZE_ON_BUFFER +               // Periodicity
        1 +                                                      // Provider/Consumer
        1;                                                       // Register/Unregister
    }

    for (auto& v : downloadVariablesToBeRegistered)
    {
      sizeRequired +=
        EncDecPrimitive::getStringSizeOnBuffer(v.second->name) + // Variable name
        EncDecHeader::PERIODICITY_SIZE_ON_BUFFER +               // Periodicity
        1 +                                                      // Provider/Consumer
        1;                                                       // Register/Unregister
    }

    if (sizeRequired > 0)
    {
      sizeRequired += EncDecHeader::MESSAGE_HEADER_SIZE_ON_BUFFER;
      sizeRequired += EncDecHeader::PACKET_ID_SIZE_ON_BUFFER;

      BufferAddress buffer = bufferManager->getBufferWithClosestSize(sizeRequired);

      int bufferOffset = 0;

      EncDecHeader::writeMessageHeader(buffer, bufferOffset, sizeRequired - EncDecHeader::MESSAGE_HEADER_SIZE_ON_BUFFER);
      EncDecHeader::writePacketId(buffer, bufferOffset, PACKET_ID_VARIABLES_REGISTRATION);

      for (auto& v : uploadVariablesToBeRegistered)
      {
        EncDecPrimitive::writeString(buffer, bufferOffset, v.second->name);
        EncDecHeader::writePeriodicity(buffer, bufferOffset, v.second->periodicity);
        EncDecPrimitive::writeBoolean(buffer, bufferOffset, true); // Client is provider of data
        EncDecPrimitive::writeBoolean(buffer, bufferOffset, true); // Do register
      }

      for (auto& v : downloadVariablesToBeRegistered)
      {
        EncDecPrimitive::writeString(buffer, bufferOffset, v.second->name);
        EncDecHeader::writePeriodicity(buffer, bufferOffset, v.second->periodicity);
        EncDecPrimitive::writeBoolean(buffer, bufferOffset, false); // Client is consumer of data
        EncDecPrimitive::writeBoolean(buffer, bufferOffset, true); // Do register
      }

      dataToServer->enqueue(new _internal::PacketToServer(buffer, bufferOffset));
    }
  }
  variablesLock.unlock();
}

void
  dds::net::connector::
  DdsConnector::unregisterVariablesFromServer()
{
  variablesLock.lock();
  {
    int sizeRequired = 0;

    for (auto& v : uploadVariables)
    {
      sizeRequired +=
        EncDecPrimitive::getStringSizeOnBuffer(v.second->name) + // Variable name
        EncDecHeader::PERIODICITY_SIZE_ON_BUFFER +               // Periodicity
        1 +                                                      // Provider/Consumer
        1;                                                       // Register/Unregister
    }

    for (auto& v : downloadVariables)
    {
      sizeRequired +=
        EncDecPrimitive::getStringSizeOnBuffer(v.second->name) + // Variable name
        EncDecHeader::PERIODICITY_SIZE_ON_BUFFER +               // Periodicity
        1 +                                                      // Provider/Consumer
        1;                                                       // Register/Unregister
    }

    if (sizeRequired > 0)
    {
      sizeRequired += EncDecHeader::MESSAGE_HEADER_SIZE_ON_BUFFER;
      sizeRequired += EncDecHeader::PACKET_ID_SIZE_ON_BUFFER;

      BufferAddress buffer = bufferManager->getBufferWithClosestSize(sizeRequired);
      int bufferOffset = 0;

      EncDecHeader::writeMessageHeader(buffer, bufferOffset, sizeRequired - EncDecHeader::MESSAGE_HEADER_SIZE_ON_BUFFER);
      EncDecHeader::writePacketId(buffer, bufferOffset, PACKET_ID_VARIABLES_REGISTRATION);

      for (auto& v : uploadVariables)
      {
        EncDecPrimitive::writeString(buffer, bufferOffset, v.second->name);
        EncDecHeader::writePeriodicity(buffer, bufferOffset, v.second->periodicity);
        EncDecPrimitive::writeBoolean(buffer, bufferOffset, true); // Client is provider of data
        EncDecPrimitive::writeBoolean(buffer, bufferOffset, false); // Do register
      }

      for (auto& v : downloadVariables)
      {
        EncDecPrimitive::writeString(buffer, bufferOffset, v.second->name);
        EncDecHeader::writePeriodicity(buffer, bufferOffset, v.second->periodicity);
        EncDecPrimitive::writeBoolean(buffer, bufferOffset, false); // Client is consumer of data
        EncDecPrimitive::writeBoolean(buffer, bufferOffset, false); // Do register
      }

      dataToServer->enqueue(new _internal::PacketToServer(buffer, bufferOffset));
    }
  }
  variablesLock.unlock();
}

void
  dds::net::connector::
  DdsConnector::sendUpdatedValuesToServer(
    std::list<_internal::variables::BaseVariable*>& vars)
{
  int sizeRequired = 0;

  for (auto& v : vars)
  {
    sizeRequired += v->getSizeOnBuffer();
  }

  if (sizeRequired > 0)
  {
    sizeRequired += EncDecHeader::MESSAGE_HEADER_SIZE_ON_BUFFER;
    sizeRequired += EncDecHeader::PACKET_ID_SIZE_ON_BUFFER;

    BufferAddress buffer = bufferManager->getBufferWithClosestSize(sizeRequired);
    int bufferOffset = 0;

    EncDecHeader::writeMessageHeader(buffer, bufferOffset, sizeRequired - EncDecHeader::MESSAGE_HEADER_SIZE_ON_BUFFER);
    EncDecHeader::writePacketId(buffer, bufferOffset, PACKET_ID_VARIABLES_UPDATE_AT_SERVER);

    for (auto& v : vars)
    {
      v->writeOnBuffer(buffer, bufferOffset);
    }

    dataToServer->enqueue(new _internal::PacketToServer(buffer, bufferOffset));
  }
}


/*************************************************************************************/
/*                                                                                   */
/* Connection Events                                                                 */
/*                                                                                   */
/*************************************************************************************/

void
  dds::net::connector::
  onConnectedWithServer(void* connector)
{
  dds::net::connector::DdsConnector* conn = (dds::net::connector::DdsConnector*)connector;

  std::string libraryVersion = conn->getLibraryVersion();

  int requiredSize = EncDecHeader::MESSAGE_HEADER_SIZE_ON_BUFFER +
    EncDecHeader::PACKET_ID_SIZE_ON_BUFFER +
    EncDecPrimitive::getStringSizeOnBuffer(conn->applicationName) +
    EncDecPrimitive::getStringSizeOnBuffer(libraryVersion);

  BufferAddress handshake = conn->bufferManager->getBufferWithClosestSize(requiredSize);
  
  int offset = 0;

  EncDecHeader::writeMessageHeader(handshake, offset, requiredSize - EncDecHeader::MESSAGE_HEADER_SIZE_ON_BUFFER);
  EncDecHeader::writePacketId(handshake, offset, PACKET_ID_HANDSHAKE);
  EncDecPrimitive::writeString(handshake, offset, conn->applicationName);
  EncDecPrimitive::writeString(handshake, offset, libraryVersion);

  conn->dataToServer->enqueue(new _internal::PacketToServer(handshake, offset));
}

void
  dds::net::connector::
  onDisconnectedFromServer(void* connector)
{
  dds::net::connector::DdsConnector* conn = (dds::net::connector::DdsConnector*)connector;

  conn->variablesLock.lock();

  for (auto& v : conn->uploadVariables)
  {
    v.second->reset();
    conn->uploadVariablesToBeRegistered[v.first] = v.second;
  }

  for (auto& v : conn->downloadVariables)
  {
    v.second->reset();
    conn->downloadVariablesToBeRegistered[v.first] = v.second;
  }

  conn->uploadVariables.clear();
  conn->downloadVariables.clear();


  conn->variablesLock.unlock();
}

/*************************************************************************************/
/*                                                                                   */
/* Data Reception                                                                    */
/*                                                                                   */
/*************************************************************************************/

bool
  dds::net::connector::
  dataReceptionWorker(void* connector)
{
  dds::net::connector::DdsConnector* conn = (dds::net::connector::DdsConnector*)connector;

  bool doneAnything = false;

  while (conn->dataFromServer->canDequeue())
  {
    doneAnything = true;

    _internal::PacketFromServer* packet = conn->dataFromServer->dequeue();

    conn->packetPreprocessor->addData(packet);

    while (true)
    {
      int size = 0;
      BufferAddress message = conn->packetPreprocessor->getSingleMessage(size);

      if (message != nullptr)
      {
        conn->parsePacket(message, size);
        conn->bufferManager->free(message);
      }
      else
      {
        break;
      }
    }
  }

  return doneAnything;
}