#ifndef DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_VARIABLES_VAR_PRIM_UDWORD_H_
#define DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_VARIABLES_VAR_PRIM_UDWORD_H_

#include "src/internal/inc/variables/base_primitive.h"


namespace dds {
  namespace net {
    namespace connector {
      namespace _internal {
        namespace variables {

          class UnsignedDWordVariable : public BasePrimitive {

          public:
            unsigned long value;

            UnsignedDWordProvider valueProvider;
            UnsignedDWordConsumer valueConsumer;

            UnsignedDWordVariable(
              std::string& name,
              Periodicity periodicity,
              UnsignedDWordProvider unsignedDWordProvider,
              UnsignedDWordConsumer unsignedDWordConsumer);

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
