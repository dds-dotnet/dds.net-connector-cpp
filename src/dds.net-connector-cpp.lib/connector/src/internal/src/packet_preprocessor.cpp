#include "src/internal/inc/packet_preprocessor.h"

#include "src/internal/inc/buffer_manager.h"
#include "src/internal/inc/packet_from_server.h"

#include "src/internal/inc/variables/enc_dec_header.h"


using namespace dds::net::connector::_internal::variables;



dds::net::connector::_internal::
  PacketPreprocessor::PacketPreprocessor(BufferManager* bufferManager)
{
  this->bufferManager = bufferManager;

  this->previousData = nullptr;
  this->previousDataSize = 0;
  this->previousDataStartIndex = 0;
  this->previousNextWriteIndex = 0;
}

dds::net::connector::_internal::
  PacketPreprocessor::~PacketPreprocessor()
{
  if (previousData != nullptr)
  {
    bufferManager->free(previousData);
  }
}

void
  dds::net::connector::_internal::
  PacketPreprocessor::addData(PacketFromServer* packet)
{
  dataLock.lock();


  
  //- 
  //- Buffer: [ - - - - - - - - - - - - - - - - - - - - - - - - - - - ]
  //-                   Data: - - - - - -
  //-           Start Index _/            \_ Next Write Index
  //- 

  BufferAddress buffer = nullptr;
  int bufferSize = 0;
  int bufferStartIndex = 0;
  int bufferNextWriteIndex = 0;

  //- 
  //- No previous data available
  //- 
  if (previousData == nullptr)
  {
    previousData = buffer = bufferManager->getBufferWithClosestSize(packet->size);
    previousDataSize = bufferSize = packet->size;
    previousDataStartIndex = bufferStartIndex = 0;
    previousNextWriteIndex = bufferNextWriteIndex = 0;
  }
  //- 
  //- We have some previous data
  //- 
  else
  {
    buffer = previousData;
    bufferSize = previousDataSize;
    bufferStartIndex = previousDataStartIndex;
    bufferNextWriteIndex = previousNextWriteIndex;
  }

  //- 
  //- Compacting the buffer
  //- 
  if (bufferNextWriteIndex != bufferStartIndex)
  {
    int timesShifted = 0;

    for (int i = 0; i < (bufferNextWriteIndex - bufferStartIndex); i++)
    {
      buffer[i] = buffer[bufferStartIndex + i];
      timesShifted++;
    }

    bufferStartIndex = 0;
    bufferNextWriteIndex -= timesShifted;
  }
  else
  {
    bufferNextWriteIndex = 0;
    bufferStartIndex = 0;
  }

  //- 
  //- Do we have enough space for the data?
  //- 
  if ((bufferSize - bufferNextWriteIndex) >= packet->size)
  {
    for (int i = 0; i < packet->size; i++)
    {
      buffer[bufferNextWriteIndex++] = packet->buffer[i];
    }

    previousDataStartIndex = bufferStartIndex;
    previousNextWriteIndex = bufferNextWriteIndex;
  }
  //- 
  //- No, we do not have enough space for data.
  //- 
  else
  {
    int newBufferSize = bufferSize + packet->size;
    BufferAddress newBuffer = bufferManager->getBufferWithClosestSize(newBufferSize);
    int newBufferStartIndex = 0;
    int newBufferNextWriteIndex = 0;

    // Copy old data
    for (int i = 0; i < bufferNextWriteIndex; i++)
    {
      newBuffer[newBufferNextWriteIndex++] = buffer[i];
    }

    bufferManager->free(buffer);


    // Copy new data
    for (int i = 0; i < packet->size; i++)
    {
      newBuffer[newBufferNextWriteIndex++] = packet->buffer[i];
    }

    previousData = newBuffer;
    previousDataSize = newBufferSize;
    previousDataStartIndex = newBufferStartIndex;
    previousNextWriteIndex = newBufferNextWriteIndex;
  }



  dataLock.unlock();

  bufferManager->free(packet->buffer);
  delete packet;
}

BufferAddress
  dds::net::connector::_internal::
  PacketPreprocessor::getSingleMessage(int& size)
{
  dataLock.lock();


  //- 
  //- Do we have any data available?
  //- 
  if (previousData != nullptr)
  {
    BufferAddress buffer = previousData;
    int bufferStartIndex = previousDataStartIndex;
    int bufferNextWriteIndex = previousNextWriteIndex;

    //- 
    //- Do we have full header?
    //- 

    int index = bufferStartIndex;

    while (index < (bufferNextWriteIndex - 1))
    {
      // Finding '##'

      if (buffer[index] == '#' &&
          buffer[index + 1] == '#')
      {
        bufferStartIndex = index;
        int readableBytes = bufferNextWriteIndex - index;

        if (readableBytes >= EncDecHeader::MESSAGE_HEADER_SIZE_ON_BUFFER)
        {
          int dataBytes = EncDecHeader::readTotalBytesInMessage(buffer, index);
          int availableBytes = bufferNextWriteIndex - index;

          if (availableBytes >= dataBytes)
          {
            BufferAddress packet = bufferManager->getBufferWithClosestSize(dataBytes);

            for (int i = 0; i < dataBytes; i++)
            {
              packet[i] = buffer[index++];
            }

            previousDataStartIndex = index;

            dataLock.unlock();
            return packet;
          }
        }

        break;
      }

      index++;
    }

    previousDataStartIndex = bufferStartIndex;

    dataLock.unlock();
    return nullptr;
  }


  //- 
  //- We do not have any data available.
  //- 
  
  dataLock.unlock();
  return nullptr;
}
