#ifndef DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_THREADED_NETWORK_CLIENT_H_
#define DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_THREADED_NETWORK_CLIENT_H_

#include <string>


namespace dds {
  namespace net {
    namespace connector {
      namespace _internal {

        class PacketFromServer;
        class PacketToServer;

        template<typename T> class SyncQueueReader;
        template<typename T> class SyncQueueWriter;

        typedef void(*connectedCallback)(void* obj);
        typedef void(*disconnectedCallback)(void* obj);

        class ThreadedNetworkClient {
        public:

          virtual SyncQueueReader<PacketFromServer>* getDataQueueFromServer() = 0;
          virtual SyncQueueWriter<PacketToServer>* getDataQueueToServer() = 0;

          virtual void setCallbackOnConnectedWithServer(connectedCallback, void* obj) = 0;
          virtual void setCallbackOnDisconnectedFromServer(disconnectedCallback, void* obj) = 0;

          virtual void connect(std::string ipv4, unsigned short tcpPort) = 0;
          virtual void disconnect() = 0;
        };

      }
    }
  }
}



#endif