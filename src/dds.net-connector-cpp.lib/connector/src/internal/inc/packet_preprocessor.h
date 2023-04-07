#ifndef DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_PACKET_PREPROCESSOR_H_
#define DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_PACKET_PREPROCESSOR_H_

#include "src/internal/inc/internal_types.h"

#include <mutex>



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
          BufferAddress getSingleMessage(int& size);

        private:
          BufferManager* bufferManager;

          std::mutex ppmutex;
          BufferAddress previousData = nullptr;
          int previousDataStartIndex = 0;
          int previousNextWriteIndex = 0;
        };

      }
    }
  }
}



#endif