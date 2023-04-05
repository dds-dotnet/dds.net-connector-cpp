#ifndef DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_VARIABLES_VAR_PRIM_UWORD_H_
#define DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_VARIABLES_VAR_PRIM_UWORD_H_

#include "src/internal/inc/variables/base_primitive.h"


namespace dds {
  namespace net {
    namespace connector {
      namespace _internal {
        namespace variables {

          class UnsignedWordVariable : public BasePrimitive {

          public:
            unsigned short value;

            UnsignedWordProvider valueProvider;
            UnsignedWordConsumer valueConsumer;

            UnsignedWordVariable(
              std::string& name,
              Periodicity periodicity,
              UnsignedWordProvider unsignedWordProvider,
              UnsignedWordConsumer unsignedWordConsumer);

            const char* getPrintableTypeName() override;

            void resetValue() override;
            bool refreshValue() override;
            void invokeValueAwaiter() override;

            int getValueSizeOnBuffer() override;
            void writeValueOnBuffer(BufferAddress buffer, int& offset) override;
          };
        }
      }
    }
  }
}



#endif
