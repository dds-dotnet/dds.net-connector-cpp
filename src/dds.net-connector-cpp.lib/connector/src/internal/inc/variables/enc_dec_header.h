#ifndef DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_VARIABLES_ENC_DEC_HEADER_H_
#define DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_VARIABLES_ENC_DEC_HEADER_H_

#include "src/internal/inc/internal_types.h"


namespace dds {
  namespace net {
    namespace connector {
      namespace _internal {
        namespace variables {

          class EncDecHeader {

          public:
            static const int VARIABLE_ID_SIZE_ON_BUFFER = 2;
            static const int VARIABLE_TYPE_SIZE_ON_BUFFER = 2;

            static void writeVariableId(BufferAddress buffer, int& offset, int id);
            static void writeVariableType(BufferAddress buffer, int& offset, VariableType variableType);
          };
        }
      }
    }
  }
}

#endif
