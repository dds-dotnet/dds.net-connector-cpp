#ifndef DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_VARIABLES_BASE_PRIMITIVE_H_
#define DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_VARIABLES_BASE_PRIMITIVE_H_

#include "src/internal/inc/variables/base_variable.h"


namespace dds {
  namespace net {
    namespace connector {
      namespace _internal {
        namespace variables {

          class BasePrimitive : public BaseVariable {

          public:
            BasePrimitive(std::string& name, PrimitiveType primitiveType, Periodicity periodicity);

            int getSubTypeSizeOnBuffer() override;
            void writeSubTypeOnBuffer(BufferAddress buffer, int& offset) override;

            PrimitiveType getPrimitiveType();

          private:
            PrimitiveType primitiveType;
          };

        }
      }
    }
  }
}



#endif
