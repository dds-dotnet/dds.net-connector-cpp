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
  /*
  int sizeRequired = 0;

            foreach (BaseVariable v in vals)
            {
                sizeRequired += v.GetSizeOnBuffer();
            }

            if (sizeRequired > 0)
            {
                sizeRequired += EncDecHeader::MESSAGE_HEADER_SIZE_ON_BUFFER;
                sizeRequired += EncDecHeader::PACKET_ID_SIZE_ON_BUFFER;

                BufferAddress buffer = bufferManager->getBufferWithClosestSize(sizeRequired);
                int bufferOffset = 0;

                EncDecHeader::writeMessageHeader(buffer, bufferOffset, sizeRequired - EncDecHeader::MESSAGE_HEADER_SIZE_ON_BUFFER);
                EncDecHeader::writePacketId(buffer, bufferOffset, PacketId.VariablesUpdateAtServer);

                foreach (BaseVariable v in vals)
                {
                    v.WriteOnBuffer(ref buffer, ref bufferOffset);
                }

                DataToServer.Enqueue(new _internal::PacketToServer(buffer, bufferOffset));
            }*/
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
  /*
  dds::net::connector::DdsConnector::DdsConnector* conn = (dds::net::connector::DdsConnector*)connector;
  byte[] handshake = new byte[
    EncDecHeader::MESSAGE_HEADER_SIZE_ON_BUFFER +
      PacketId.HandShake.GetSizeOnBuffer() +
      2 + Encoding.Unicode.GetBytes(ApplicationName).Length +
      2 + Encoding.Unicode.GetBytes(LibraryVersion).Length];
  int offset = 0;

  handshake.WriteMessageHeader(ref offset, handshake.Length - EncDecHeader::MESSAGE_HEADER_SIZE_ON_BUFFER);
  handshake.WritePacketId(ref offset, PacketId.HandShake);
  handshake.WriteString(ref offset, ApplicationName);
  handshake.WriteString(ref offset, LibraryVersion);

  DataToServer.Enqueue(new(handshake, offset));*/
}

void
  dds::net::connector::
  onDisconnectedFromServer(void* connector)
{
  /*
  variablesLock.lock();
  {
    foreach(KeyValuePair<string, BaseVariable> v in uploadVariables)
    {
      v.second->Reset();
      uploadVariablesToBeRegistered.Add(v.first, v.Value);
    }

    foreach(KeyValuePair<string, BaseVariable> v in downloadVariables)
    {
      v.second->Reset();
      downloadVariablesToBeRegistered.Add(v.first, v.Value);
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

bool
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