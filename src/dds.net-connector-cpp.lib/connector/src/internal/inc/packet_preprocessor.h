#ifndef DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_PACKET_PREPROCESSOR_H_
#define DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_PACKET_PREPROCESSOR_H_

#include "src/internal/inc/internal_types.h"



namespace dds {
  namespace net {
    namespace connector {
      namespace _internal {

        class BufferManager;
        class PacketFromServer;

        class PacketPreprocessor {
        public:

          PacketPreprocessor(BufferManager* bufferManager);
          ~PacketPreprocessor();

          void addData(PacketFromServer* packet);
          BufferAddress getSingleMessage();

        private:
          BufferManager* bufferManager;
        };

      }
    }
  }
}



#endif