#ifndef DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_BUFFER_MANAGER_H_
#define DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_BUFFER_MANAGER_H_

#include "src/internal/inc/internal_types.h"

#include <list>
#include <mutex>


namespace dds {
  namespace net {
    namespace connector {
      namespace _internal {

        typedef struct {
          BufferAddress address;
          int size;
          bool isFree;
        } BufferDefinition;

        class BufferManager {
        public:

          BufferManager();
          ~BufferManager();

          BufferAddress get1k();
          BufferAddress get2k();
          BufferAddress get4k();
          BufferAddress get8k();
          BufferAddress get16k();
          BufferAddress get32k();
          BufferAddress get64k();
          BufferAddress get128k();
          BufferAddress get256k();
          BufferAddress get512k();
          BufferAddress get1M();
          BufferAddress get2M();
          BufferAddress get4M();
          BufferAddress get8M();
          BufferAddress get16M();
          BufferAddress get32M();
          BufferAddress get64M();

          BufferAddress get(int size);
          void free(BufferAddress freeBuffer);
          void GC();


        private:
          std::mutex buffLock;
          std::list<BufferDefinition> buffers;
        };

      }
    }
  }
}



#endif