#ifndef DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_VARIABLES_VAR_RAW_BYTES_H_
#define DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_VARIABLES_VAR_RAW_BYTES_H_

#include "src/internal/inc/variables/base_variable.h"
#include "src/internal/inc/buffer_manager.h"


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
              RawBytesConsumer rawBytesConsumer,
              BufferManager *bufferManager);

            std::string getPrintableTypeName() override;

            int getSubTypeSizeOnBuffer() override;
            void writeSubTypeOnBuffer(BufferAddress buffer, int& offset) override;

            void resetValue() override;
            bool refreshValue() override;
            void invokeValueAwaiter() override;

            int getValueSizeOnBuffer() override;
            void writeValueOnBuffer(BufferAddress buffer, int& offset) override;

            bool updateData(BufferAddress buffer, int size);


          private:
            BufferManager* bufferManager;
          };

        }
      }
    }
  }
}



#endif
