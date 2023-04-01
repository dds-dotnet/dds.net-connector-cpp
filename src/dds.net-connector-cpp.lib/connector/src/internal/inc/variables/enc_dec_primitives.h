#ifndef DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_VARIABLES_ENC_DEC_PRIMITIVES_H_
#define DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_VARIABLES_ENC_DEC_PRIMITIVES_H_

#include "inc/types.h"
#include "src/internal/inc/internal_types.h"


namespace dds {
  namespace net {
    namespace connector {
      namespace _internal {
        namespace variables {

          class EncDecPrimitives {

          public:
            static const int PRIMITIVE_TYPE_SIZE_ON_BUFFER = 1;

            static void writePrimitiveType(BufferAddress buffer, int& offset, PrimitiveType value);
            static PrimitiveType readPrimitiveType(BufferAddress buffer, int& offset);
          };
        }
      }
    }
  }
}

#endif
