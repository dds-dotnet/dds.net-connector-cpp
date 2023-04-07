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
static char errorMessage[1024];

void
  dds::net::connector::
  DdsConnector::parseVariablesUpdateFromServer(void* buffer, int size, int& offset)
{
  BufferAddress data = (BufferAddress)buffer;


  list<BaseVariable*> updatedVariables;



  variablesLock.lock();


  Periodicity periodicity = EncDecHeader::readPeriodicity(data, offset);

  while (offset < size)
  {
    unsigned short id = EncDecPrimitive::readUnsignedWord(data, offset);
    VariableType mainType = EncDecHeader::readVariableType(data, offset);
    BaseVariable* var = nullptr;

    for (auto& v : downloadVariables)
    {
      if (id == v.second->id)
      {
        var = v.second;
        break;
      }
    }

    /************************************************************************/
    /*                                                                      */
    /* Processing RawBytes variable                                         */
    /*                                                                      */
    /************************************************************************/
    if (mainType == VARIABLE_TYPE_RAW_BYTES)
    {
      int totalBytes = (int)EncDecPrimitive::readUnsignedDWord(data, offset);

      //- 
      //- The input value is not null
      //- 
      if (totalBytes > 0)
      {
        //- 
        //- Not enough data is available
        //- 
        if (totalBytes + offset > size)
        {
          if (var != nullptr)
          {
#if TARGET_PLATFORM == PLATFORM_WINDOWS
            sprintf_s(errorMessage, sizeof(errorMessage),
#else
            sprintf(errorMessage,
#endif
              "Insufficient data provided for %s", var->name.c_str());

            throw Error(errorMessage);
          }
          else
          {
            throw Error("Insufficient data provided for unknown RawBytes variable");
          }
        }

        //- 
        //- Data is available and the types are matching
        //- 
        if (var != nullptr &&
            var->variableType == VARIABLE_TYPE_RAW_BYTES)
        {
          RawBytesVariable* rbv = (RawBytesVariable*)var;

          BufferAddress bytes = bufferManager->getBufferWithClosestSize(totalBytes);

          for (int i = 0; i < totalBytes; i++)
          {
            bytes[i] = data[offset++];
          }

          if (rbv->updateData(bytes, totalBytes))
          {
            updatedVariables.push_back(var);
          }
        }
        //- 
        //- Data is available but the types are not matching
        //- 
        else
        {
          offset += totalBytes;
        }
      }
      //- 
      //- The input value is null
      //- 
      else
      {
        if (var != nullptr &&
            var->variableType == VARIABLE_TYPE_RAW_BYTES)
        {
          RawBytesVariable* rbv = (RawBytesVariable*)var;

          if (rbv->updateData(nullptr, 0))
          {
            updatedVariables.push_back(var);
          }
        }
      }
    }
    /************************************************************************/
    /*                                                                      */
    /* Processing Primitive variable                                         */
    /*                                                                      */
    /************************************************************************/
    else if (mainType == VARIABLE_TYPE_PRIMITIVE)
    {
      //- 
      //- Discarding the value when we do not have locally registered variable.
      //- 
      if (var == nullptr || var->variableType != VARIABLE_TYPE_PRIMITIVE)
      {
        PrimitiveType pt = EncDecPrimitive::readPrimitiveType(data, offset);

        switch (pt)
        {
        case PRIMITIVE_TYPE_STRING:         EncDecPrimitive::readString(data, offset);        break;
        case PRIMITIVE_TYPE_BOOLEAN:        EncDecPrimitive::readBoolean(data, offset);       break;
        case PRIMITIVE_TYPE_BYTE:           EncDecPrimitive::readByte(data, offset);          break;
        case PRIMITIVE_TYPE_WORD:           EncDecPrimitive::readWord(data, offset);          break;
        case PRIMITIVE_TYPE_DWORD:          EncDecPrimitive::readDWord(data, offset);         break;
        case PRIMITIVE_TYPE_QWORD:          EncDecPrimitive::readQWord(data, offset);         break;
        case PRIMITIVE_TYPE_UNSIGNED_BYTE:  EncDecPrimitive::readUnsignedByte(data, offset);  break;
        case PRIMITIVE_TYPE_UNSIGNED_WORD:  EncDecPrimitive::readUnsignedWord(data, offset);  break;
        case PRIMITIVE_TYPE_UNSIGNED_DWORD: EncDecPrimitive::readUnsignedDWord(data, offset); break;
        case PRIMITIVE_TYPE_UNSIGNED_QWORD: EncDecPrimitive::readUnsignedQWord(data, offset); break;
        case PRIMITIVE_TYPE_SINGLE:         EncDecPrimitive::readSingle(data, offset);        break;
        case PRIMITIVE_TYPE_DOUBLE:         EncDecPrimitive::readDouble(data, offset);        break;
        case PRIMITIVE_TYPE_UNKNOWN:                                                          break;
        }

        if (var != nullptr && var->variableType != VARIABLE_TYPE_PRIMITIVE)
        {
#if TARGET_PLATFORM == PLATFORM_WINDOWS
          sprintf_s(errorMessage, sizeof(errorMessage),
#else
          sprintf(errorMessage,
#endif
            "Cannot assign primitive value to non-primitive variable %s", var->name.c_str());

          logger->error(errorMessage);
        }
      }

      //- 
      //- Processing the variable value when we have local primitive variable.
      //- 
      else if (var != nullptr && var->variableType == VARIABLE_TYPE_PRIMITIVE)
      {
        BasePrimitive* bpv = (BasePrimitive*)var;

        PrimitiveType pt = EncDecPrimitive::readPrimitiveType(data, offset);
        bool valueUpdated = false;

        switch (pt)
        {
        case PRIMITIVE_TYPE_STRING:
          {
            string valueRead = EncDecPrimitive::readString(data, offset);
            valueUpdated = updatePrimitiveVariableWithString(bpv, valueRead);
          }
          break;
        case PRIMITIVE_TYPE_BOOLEAN:        valueUpdated = updatePrimitiveVariableWithBoolean(bpv, EncDecPrimitive::readBoolean(data, offset));             break;
        case PRIMITIVE_TYPE_BYTE:           valueUpdated = updatePrimitiveVariableWithByte(bpv, EncDecPrimitive::readByte(data, offset));                   break;
        case PRIMITIVE_TYPE_WORD:           valueUpdated = updatePrimitiveVariableWithWord(bpv, EncDecPrimitive::readWord(data, offset));                   break;
        case PRIMITIVE_TYPE_DWORD:          valueUpdated = updatePrimitiveVariableWithDWord(bpv, EncDecPrimitive::readDWord(data, offset));                 break;
        case PRIMITIVE_TYPE_QWORD:          valueUpdated = updatePrimitiveVariableWithQWord(bpv, EncDecPrimitive::readQWord(data, offset));                 break;
        case PRIMITIVE_TYPE_UNSIGNED_BYTE:  valueUpdated = updatePrimitiveVariableWithUnsignedByte(bpv, EncDecPrimitive::readUnsignedByte(data, offset));   break;
        case PRIMITIVE_TYPE_UNSIGNED_WORD:  valueUpdated = updatePrimitiveVariableWithUnsignedWord(bpv, EncDecPrimitive::readUnsignedWord(data, offset));   break;
        case PRIMITIVE_TYPE_UNSIGNED_DWORD: valueUpdated = updatePrimitiveVariableWithUnsignedDWord(bpv, EncDecPrimitive::readUnsignedDWord(data, offset)); break;
        case PRIMITIVE_TYPE_UNSIGNED_QWORD: valueUpdated = updatePrimitiveVariableWithUnsignedQWord(bpv, EncDecPrimitive::readUnsignedQWord(data, offset)); break;
        case PRIMITIVE_TYPE_SINGLE:         valueUpdated = updatePrimitiveVariableWithSingle(bpv, EncDecPrimitive::readSingle(data, offset));               break;
        case PRIMITIVE_TYPE_DOUBLE:         valueUpdated = updatePrimitiveVariableWithDouble(bpv, EncDecPrimitive::readDouble(data, offset));               break;
        case PRIMITIVE_TYPE_UNKNOWN:                                                                                                                        break;
        }

        if (valueUpdated)
        {
          updatedVariables.push_back(var);
        }
      }
    }

  } // while (offset < data.Length)


  variablesLock.unlock();



  for (auto& v : updatedVariables)
  {
    v->invokeValueAwaiter();
  }
}
