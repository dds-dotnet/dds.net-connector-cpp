#ifndef DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_VARIABLES_VAR_PRIM_SINGLE_H_
#define DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_VARIABLES_VAR_PRIM_SINGLE_H_

#include "src/internal/inc/variables/base_primitive.h"


namespace dds {
  namespace net {
    namespace connector {
      namespace _internal {
        namespace variables {

          class SingleVariable : public BasePrimitive {

          public:
            float value;

            SingleProvider valueProvider;
            SingleConsumer valueConsumer;

            SingleVariable(
              std::string& name,
              Periodicity periodicity,
              SingleProvider singleProvider,
              SingleConsumer singleConsumer);

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
