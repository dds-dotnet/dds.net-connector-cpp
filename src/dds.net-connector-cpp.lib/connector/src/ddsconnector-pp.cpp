#include "inc/ddsconnector.h"

#include "inc/error.h"

#include "src/internal/inc/internal_types.h"
#include "src/internal/inc/buffer_manager.h"

#include "src/internal/inc/variables/base_variable.h"
#include "src/internal/inc/variables/base_primitive.h"
#include "src/internal/inc/variables/var_prim_boolean.h"
#include "src/internal/inc/variables/var_prim_byte.h"
#include "src/internal/inc/variables/var_prim_double.h"
#include "src/internal/inc/variables/var_prim_dword.h"
#include "src/internal/inc/variables/var_prim_qword.h"
#include "src/internal/inc/variables/var_prim_single.h"
#include "src/internal/inc/variables/var_prim_string.h"
#include "src/internal/inc/variables/var_prim_ubyte.h"
#include "src/internal/inc/variables/var_prim_udword.h"
#include "src/internal/inc/variables/var_prim_uqword.h"
#include "src/internal/inc/variables/var_prim_uword.h"
#include "src/internal/inc/variables/var_prim_word.h"
#include "src/internal/inc/variables/var_raw_bytes.h"

#include "src/internal/inc/variables/enc_dec_header.h"
#include "src/internal/inc/variables/enc_dec_primitive.h"

#include <string>
#include <exception>


using namespace std;
using namespace dds::net::connector::_internal::variables;


/*****************************************************************************/
/*                                                                           */
/* Main Parsing                                                              */
/*                                                                           */
/*****************************************************************************/
void
  dds::net::connector::DdsConnector::
  parsePacket(void* buffer, int size)
{
  BufferAddress data = (BufferAddress)buffer;

  BufferAddress logMessage = bufferManager->get4k();
#if TARGET_PLATFORM == PLATFORM_WINDOWS
  int logMessageSize = 4096;
#endif

  int offset = 0;

  try
  {
    PacketId packetId = EncDecHeader::readPacketId(data, offset);

    switch (packetId)
    {
    case PACKET_ID_HANDSHAKE:
      {
        string serverName = EncDecPrimitive::readString(data, offset);
        string serverVersion = EncDecPrimitive::readString(data, offset);

#if TARGET_PLATFORM == PLATFORM_WINDOWS
        sprintf_s(logMessage, logMessageSize,
#else
        sprintf(logMessage,
#endif
          "Server = %s v%s", serverName.c_str(), serverVersion.c_str());

        logger->info(logMessage);
      }
      break;

    case PACKET_ID_VARIABLES_REGISTRATION:
      parseVariablesRegistration(data, size, offset);
      break;

    case PACKET_ID_VARIABLES_UPDATE_AT_SERVER:
      parseVariablesUpdateAtServer(data, size, offset);
      break;

    case PACKET_ID_VARIABLES_UPDATE_FROM_SERVER:
      parseVariablesUpdateFromServer(data, size, offset);
      break;

    case PACKET_ID_ERROR_RESPONSE_FROM_SERVER:
      {
        string errorMessage = EncDecPrimitive::readString(data, offset);

#if TARGET_PLATFORM == PLATFORM_WINDOWS
        sprintf_s(logMessage, logMessageSize,
#else
        sprintf(logMessage,
#endif
          "Server Error: %s", errorMessage.c_str());

        logger->error(logMessage);
      }
      break;

    case PACKET_ID_UNKNOWN:
      logger->error("Unknown message received from the server.");
      break;
    }
  }
  catch (std::exception& e)
  {
#if TARGET_PLATFORM == PLATFORM_WINDOWS
    sprintf_s(logMessage, logMessageSize,
#else
    sprintf(logMessage,
#endif
      "Packet parsing error: %s", e.what());
    
    logger->error(logMessage);
  }

  bufferManager->free(logMessage);
}



/*****************************************************************************/
/*                                                                           */
/* Variables' Registration                                                   */
/*                                                                           */
/*****************************************************************************/
void
  dds::net::connector::
  DdsConnector::parseVariablesRegistration(void* buffer, int size, int& offset)
{
  BufferAddress data = (BufferAddress)buffer;



  variablesLock.lock();


  while (offset < size)
  {
    string variableName = EncDecPrimitive::readString(data, offset);
    unsigned short variableId = EncDecPrimitive::readUnsignedWord(data, offset);
    bool isRegister = EncDecPrimitive::readBoolean(data, offset);

    if (isRegister)
    {
      if (downloadVariablesToBeRegistered.count(variableName) > 0)
      {
        BaseVariable* theVar = downloadVariablesToBeRegistered[variableName];
        theVar->assignId(variableId);

        downloadVariables[variableName] = theVar;
        downloadVariablesToBeRegistered.erase(variableName);
      }
      else if (uploadVariablesToBeRegistered.count(variableName) > 0)
      {
        BaseVariable* theVar = uploadVariablesToBeRegistered[variableName];
        theVar->assignId(variableId);

        uploadVariables[variableName] = theVar;
        uploadVariablesToBeRegistered.erase(variableName);
      }
    }
    else
    {
      if (downloadVariables.count(variableName) > 0)
      {
        BaseVariable* theVar = downloadVariables[variableName];
        theVar->reset();

        downloadVariablesToBeRegistered[variableName] = theVar;
        downloadVariables.erase(variableName);
      }
      else if (uploadVariables.count(variableName) > 0)
      {
        BaseVariable* theVar = uploadVariables[variableName];
        theVar->reset();

        uploadVariablesToBeRegistered[variableName] = theVar;
        uploadVariables.erase(variableName);
      }
    }
  }


  variablesLock.unlock();
}



/*****************************************************************************/
/*                                                                           */
/* Variables' Update at the Server                                           */
/*                                                                           */
/*****************************************************************************/
void
  dds::net::connector::
  DdsConnector::parseVariablesUpdateAtServer(void* buffer, int size, int& offset)
{
  BufferAddress data = (BufferAddress)buffer;

  BufferAddress logMessage = bufferManager->get4k();
#if TARGET_PLATFORM == PLATFORM_WINDOWS
  int logMessageSize = 4096;
#endif


  variablesLock.lock();
  

  while (offset < size)
  {
    unsigned short variableId = EncDecPrimitive::readUnsignedWord(data, offset);
    string errorMessage = EncDecPrimitive::readString(data, offset);

    for (auto& v : uploadVariables)
    {
      if (v.second->id == variableId)
      {

#if TARGET_PLATFORM == PLATFORM_WINDOWS
        sprintf_s(logMessage, logMessageSize,
#else
        sprintf(logMessage,
#endif
          "Variable %s cannot be updated at the server - %s", v.second->name.c_str(), errorMessage.c_str());

        logger->error(logMessage);
        break;
      }
    }
  }


  variablesLock.unlock();


  bufferManager->free(logMessage);
}



/*****************************************************************************/
/*                                                                           */
/* Variables' Update from the Server                                         */
/*                                                                           */
/*****************************************************************************/
void
  dds::net::connector::
  DdsConnector::parseVariablesUpdateFromServer(void* buffer, int size, int& offset)
{
}
