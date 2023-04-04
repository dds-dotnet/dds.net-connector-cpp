#ifndef DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_VARIABLES_VAR_PRIM_DOUBLE_H_
#define DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_VARIABLES_VAR_PRIM_DOUBLE_H_

#include "src/internal/inc/variables/base_primitive.h"


namespace dds {
  namespace net {
    namespace connector {
      namespace _internal {
        namespace variables {

          class DoubleVariable : public BasePrimitive {

          public:
            double value;

            DoubleProvider valueProvider;
            DoubleConsumer valueConsumer;

            DoubleVariable(
              std::string& name,
              Periodicity periodicity,
              DoubleProvider doubleProvider,
              DoubleConsumer doubleConsumer);

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
