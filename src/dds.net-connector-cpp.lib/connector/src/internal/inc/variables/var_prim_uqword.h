#ifndef DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_VARIABLES_VAR_PRIM_UQWORD_H_
#define DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_VARIABLES_VAR_PRIM_UQWORD_H_

#include "src/internal/inc/variables/base_primitive.h"


namespace dds {
  namespace net {
    namespace connector {
      namespace _internal {
        namespace variables {

          class UnsignedQWordVariable : public BasePrimitive {

          public:
            unsigned long long value;

            UnsignedQWordProvider valueProvider;
            UnsignedQWordConsumer valueConsumer;

            UnsignedQWordVariable(
              std::string& name,
              Periodicity periodicity,
              UnsignedQWordProvider unsignedQWordProvider,
              UnsignedQWordConsumer unsignedQWordConsumer);

            std::string getPrintableTypeName() override;

            void resetValue() override;
            bool refreshValue() override;
            void invokeValueAwaiter() override;

            int getValueSizeOnBuffer() override;
            void writeValueOnBuffer(BufferAddress buffer, int& offset) override;
        }
      }
    }
  }
}



#endif
