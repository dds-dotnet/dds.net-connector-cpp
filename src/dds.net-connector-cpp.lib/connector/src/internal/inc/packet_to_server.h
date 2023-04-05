#ifndef DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_PACKET_TO_SERVER_H_
#define DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_PACKET_TO_SERVER_H_

#include "src/internal/inc/internal_types.h"


namespace dds {
  namespace net {
    namespace connector {
      namespace _internal {

        class PacketToServer {
        public:
          BufferAddress buffer;
          int size;

          PacketToServer(BufferAddress buffer, int size);
        };

      }
    }
  }
}



#endif