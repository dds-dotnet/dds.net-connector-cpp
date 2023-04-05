#ifndef DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_BUFFER_MANAGER_H_
#define DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_BUFFER_MANAGER_H_



namespace dds {
  namespace net {
    namespace connector {
      namespace _internal {

        class BufferManager;

        class PacketPreprocessor {
        public:

          PacketPreprocessor(BufferManager* bufferManager);
          ~PacketPreprocessor();

        private:
          BufferManager* bufferManager;
        };

      }
    }
  }
}



#endif