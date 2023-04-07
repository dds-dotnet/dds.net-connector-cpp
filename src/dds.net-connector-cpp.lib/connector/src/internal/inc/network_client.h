#ifndef DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_NETWORK_CLIENT_H_
#define DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_NETWORK_CLIENT_H_

#include "src/internal/inc/threaded_network_client.h"


namespace dds {
  namespace net {
    namespace connector {
      namespace _internal {

        class BufferManager;
        template<typename T> class SyncQueue;

        class NetworkClient : public dds::net::connector::_internal::ThreadedNetworkClient {
        public:
          NetworkClient(BufferManager*);

          virtual SyncQueueReader<PacketFromServer*>* getDataQueueFromServer() override;
          virtual SyncQueueWriter<PacketToServer*>* getDataQueueToServer() override;

          virtual void setCallbackOnConnectedWithServer(connectedCallback, void* obj) override;
          virtual void setCallbackOnDisconnectedFromServer(disconnectedCallback, void* obj) override;

          virtual void connect(std::string ipv4, unsigned short tcpPort) override;
          virtual void disconnect() override;

        private:
          BufferManager* bufferManager;

          connectedCallback onConnected;
          void* onConnectedObj;

          disconnectedCallback onDisconnected;
          void* onDisconnectedObj;

          SyncQueue<PacketToServer*>* dataToServerQueue;
          SyncQueue<PacketFromServer*>* dataFromServerQueue;
        };

      }
    }
  }
}



#endif