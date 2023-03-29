#ifndef DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_VARIABLES_BASE_VARIABLE_H_
#define DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_VARIABLES_BASE_VARIABLE_H_

#include "inc/types.h"

#include "src/internal/inc/macros.h"
#include "src/internal/inc/internal_types.h"

#include "src/internal/variables/enc_dec_header.h"

#include <string>
#include <exception>

#include <stdio.h>


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

            BaseVariable(std::string& name, VariableType variableType, Periodicity periodicity)
            {
              this->id = -1;
              this->name = name;
              this->variableType = variableType;
              this->periodicity = periodicity;
            }

            void assignId(int id)
            {
              if (this->id != -1)
              {
                char message[200];
                sprintf_s(message, sizeof(message),
                  "Variable %s has already been assigned with an ID", name.c_str());

                throw std::exception(message);
              }

              if (id < 0 || id > MAX_USHORT_VALUE)
              {
                char message[200];
                sprintf_s(message, sizeof(message),
                  "Variable %s cannot be assigned with out-of-range ID %d", name.c_str(), id);

                throw std::invalid_argument(message);
              }

              this->id = id;
            }

            void reset()
            {
              id = -1;
              resetValue();
            }
            
            virtual void resetValue() = 0;
            virtual std::string getPrintableTypeName() = 0;
            virtual bool refreshValue() = 0;
            virtual void invokeValueAwaiter() = 0;

            int getSizeOnBuffer()
            {
              return
                EncDecHeader::ID_SIZE_ON_BUFFER +
                EncDecHeader::VARIABLE_TYPE_SIZE_ON_BUFFER +
                getSubTypeSizeOnBuffer() +
                getValueSizeOnBuffer();
            }
            
            virtual int getSubTypeSizeOnBuffer() = 0;
            virtual int getValueSizeOnBuffer() = 0;

            void writeOnBuffer(BufferAddress buffer, int& offset)
            {
              EncDecHeader::writeId(buffer, offset, id);
              EncDecHeader::writeVariableType(buffer, offset, variableType);

              writeSubTypeOnBuffer(buffer, offset);
              writeValueOnBuffer(buffer, offset);
            }
            
            virtual void writeSubTypeOnBuffer(BufferAddress buffer, int& offset) = 0;
            virtual void writeValueOnBuffer(BufferAddress buffer, int& offset) = 0;
          };

        }
      }
    }
  }
}



#endif
