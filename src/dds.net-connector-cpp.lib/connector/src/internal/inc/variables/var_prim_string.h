#ifndef DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_VARIABLES_VAR_PRIM_STRING_H_
#define DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_VARIABLES_VAR_PRIM_STRING_H_

#include "src/internal/inc/variables/base_primitive.h"


namespace dds {
  namespace net {
    namespace connector {
      namespace _internal {
        namespace variables {

          class StringVariable : public BasePrimitive {

          public:
            std::string value;

            StringProvider valueProvider;
            StringConsumer valueConsumer;

            StringVariable(
              std::string& name,
              Periodicity periodicity,
              StringProvider stringProvider,
              StringConsumer stringConsumer);

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
