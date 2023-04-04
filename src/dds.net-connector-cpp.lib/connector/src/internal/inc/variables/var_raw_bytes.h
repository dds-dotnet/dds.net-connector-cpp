#ifndef DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_VARIABLES_VAR_RAW_BYTES_H_
#define DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_VARIABLES_VAR_RAW_BYTES_H_

#include "src/internal/inc/variables/base_variable.h"


namespace dds {
  namespace net {
    namespace connector {
      namespace _internal {
        namespace variables {

          class RawBytesVariable : public BaseVariable {

          public:
            unsigned char* data;
            int dataSize;

            RawBytesProvider valueProvider;
            RawBytesConsumer valueConsumer;

            RawBytesVariable(
              std::string& name,
              Periodicity periodicity,
              RawBytesProvider rawBytesProvider,
              RawBytesConsumer rawBytesConsumer);

            int getSubTypeSizeOnBuffer() override;
            void writeSubTypeOnBuffer(BufferAddress buffer, int& offset) override;
          };

        }
      }
    }
  }
}



#endif
