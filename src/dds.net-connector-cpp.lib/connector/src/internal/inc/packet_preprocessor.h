#ifndef DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_PACKET_PREPROCESSOR_H_
#define DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_PACKET_PREPROCESSOR_H_



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

        private:
          BufferManager* bufferManager;
        };

      }
    }
  }
}



#endif