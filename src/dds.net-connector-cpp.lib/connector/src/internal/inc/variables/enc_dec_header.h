#ifndef DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_VARIABLES_ENC_DEC_HEADER_H_
#define DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_VARIABLES_ENC_DEC_HEADER_H_

#include "inc/types.h"
#include "src/internal/inc/internal_types.h"


namespace dds {
  namespace net {
    namespace connector {
      namespace _internal {
        namespace variables {

          class EncDecHeader {

          public:
            static const int MESSAGE_HEADER_SIZE_ON_BUFFER = 6; // ##[Total Bytes]
            static const int PACKET_ID_SIZE_ON_BUFFER = 2;
            static const int VARIABLE_ID_SIZE_ON_BUFFER = 2;
            static const int VARIABLE_TYPE_SIZE_ON_BUFFER = 2;
            static const int PERIODICITY_SIZE_ON_BUFFER = 1;

            static void writeMessageHeader(BufferAddress buffer, int& offset, int totalBytes);
            static int readTotalBytesInMessage(BufferAddress buffer, int& offset);

            static void writePacketId(BufferAddress buffer, int& offset, PacketId id);
            static PacketId readPacketId(BufferAddress buffer, int& offset);

            static void writeVariableId(BufferAddress buffer, int& offset, int id);
            static int readVariableId(BufferAddress buffer, int& offset);

            static void writeVariableType(BufferAddress buffer, int& offset, VariableType variableType);
            static VariableType readVariableType(BufferAddress buffer, int& offset);

            static void writePeriodicity(BufferAddress buffer, int& offset, Periodicity value);
            static Periodicity readPeriodicity(BufferAddress buffer, int& offset);
          };
        }
      }
    }
  }
}

#endif
