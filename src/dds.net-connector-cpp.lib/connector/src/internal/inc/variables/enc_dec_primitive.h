#ifndef DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_VARIABLES_ENC_DEC_PRIMITIVE_H_
#define DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_VARIABLES_ENC_DEC_PRIMITIVE_H_

#include "inc/types.h"
#include "src/internal/inc/internal_types.h"

#include <string>


namespace dds {
  namespace net {
    namespace connector {
      namespace _internal {
        namespace variables {

          class EncDecPrimitive {

          public:
            static const int PRIMITIVE_TYPE_SIZE_ON_BUFFER = 1;

            static PrimitiveType readPrimitiveType(BufferAddress buffer, int& offset);
            static void writePrimitiveType(BufferAddress buffer, int& offset, PrimitiveType value);

            static std::string& readString(BufferAddress buffer, int& offset);
            static void writeString(BufferAddress buffer, int& offset, std::string& value);

            static bool readBoolean(BufferAddress buffer, int& offset);
            static void writeBoolean(BufferAddress buffer, int& offset, bool value);

            static char readByte(BufferAddress buffer, int& offset);
            static void writeByte(BufferAddress buffer, int& offset, char value);

            static short readWord(BufferAddress buffer, int& offset);
            static void writeWord(BufferAddress buffer, int& offset, short value);

            static long readDWord(BufferAddress buffer, int& offset);
            static void writeDWord(BufferAddress buffer, int& offset, long value);

            static long long readQWord(BufferAddress buffer, int& offset);
            static void writeQWord(BufferAddress buffer, int& offset, long long value);

            static unsigned char readUnsignedByte(BufferAddress buffer, int& offset);
            static void writeUnsignedByte(BufferAddress buffer, int& offset, unsigned char value);
            
            static unsigned short readUnsignedWord(BufferAddress buffer, int& offset);
            static void writeUnsignedWord(BufferAddress buffer, int& offset, unsigned short value);
            
            static unsigned long readUnsignedDWord(BufferAddress buffer, int& offset);
            static void writeUnsignedDWord(BufferAddress buffer, int& offset, unsigned long value);
            
            static unsigned long long readUnsignedQWord(BufferAddress buffer, int& offset);
            static void writeUnsignedQWord(BufferAddress buffer, int& offset, unsigned long long value);
            
            static float readSingle(BufferAddress buffer, int& offset);
            static void writeSingle(BufferAddress buffer, int& offset, float value);
            
            static double readDouble(BufferAddress buffer, int& offset);
            static void writeDouble(BufferAddress buffer, int& offset, double value);

          private:
            static bool isLittleEndian();
          };
        }
      }
    }
  }
}

#endif
