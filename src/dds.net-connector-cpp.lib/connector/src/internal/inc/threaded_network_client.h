#ifndef DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_THREADED_NETWORK_CLIENT_H_
#define DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_THREADED_NETWORK_CLIENT_H_

#include <string>


namespace dds {
  namespace net {
    namespace connector {
      namespace _internal {

        class SyncQueueReader;
        class SyncQueueWriter;

        typedef void(*connectedCallback)();
        typedef void(*disconnectedCallback)();

        class ThreadedNetworkClient {
        public:

          virtual SyncQueueReader* getDataQueueFromServer() = 0;
          virtual SyncQueueWriter* getDataQueueToServer() = 0;

          virtual void setCallbackOnConnectedWithServer(connectedCallback) = 0;
          virtual void setCallbackOnDisconnectedFromServer(disconnectedCallback) = 0;

          virtual void connect(std::string ipv4, unsigned short tcpPort) = 0;
          virtual void disconnect() = 0;
        };

      }
    }
  }
}



#endif