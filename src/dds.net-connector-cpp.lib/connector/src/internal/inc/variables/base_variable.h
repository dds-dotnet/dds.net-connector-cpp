#ifndef DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_VARIABLES_BASE_VARIABLE_H_
#define DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_VARIABLES_BASE_VARIABLE_H_

#include "inc/types.h"

#include "src/internal/inc/internal_types.h"

#include <string>


namespace dds {
  namespace net {
    namespace connector {
      namespace _internal {
        namespace variables {

          class BaseVariable {

          public:
            int id;
            std::string name;
            VariableType variableType;
            Periodicity periodicity;

            BaseVariable(std::string& name, VariableType variableType, Periodicity periodicity);
            virtual ~BaseVariable();
            
            void assignId(int id);
            void reset();
            
            virtual const char* getPrintableTypeName() = 0;

            virtual void resetValue() = 0;
            virtual bool refreshValue() = 0;
            virtual void invokeValueAwaiter() = 0;

            int getSizeOnBuffer();
            virtual int getSubTypeSizeOnBuffer() = 0;
            virtual int getValueSizeOnBuffer() = 0;

            void writeOnBuffer(BufferAddress buffer, int& offset);
            virtual void writeSubTypeOnBuffer(BufferAddress buffer, int& offset) = 0;
            virtual void writeValueOnBuffer(BufferAddress buffer, int& offset) = 0;
          };

        }
      }
    }
  }
}



#endif
