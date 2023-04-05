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