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
          void* address;
          int size;
          bool isFree;
        } BufferDefinition;

        class BufferManager {
        public:

          BufferManager();

          void* get1k();
          void* get2k();
          void* get4k();
          void* get8k();
          void* get16k();
          void* get32k();
          void* get64k();
          void* get128k();
          void* get256k();
          void* get512k();
          void* get1M();
          void* get2M();
          void* get4M();
          void* get8M();
          void* get16M();
          void* get32M();
          void* get64M();

          void* get(int size);
          void free(void* freeBuffer);
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