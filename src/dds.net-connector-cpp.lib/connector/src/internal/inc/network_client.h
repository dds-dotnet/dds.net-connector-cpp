#ifndef DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_NETWORK_CLIENT_H_
#define DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_NETWORK_CLIENT_H_

#include "src/internal/inc/threaded_network_client.h"

#include <string>
#include <mutex>
#include <thread>


namespace dds {
  namespace net {
    namespace connector {
      namespace _internal {

        class BufferManager;
        class NetworkClient;
        template<typename T> class SyncQueue;
        void ioThreadFunc(NetworkClient* client);



        class NetworkClient : public dds::net::connector::_internal::ThreadedNetworkClient {
        public:
          NetworkClient(BufferManager*, int dataToServerQueueSize = 1000, int dataFromServerQueueSize = 1000);

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

          std::mutex dataLock;

          std::string ipv4;
          int tcpPort;

          bool isIOThreadStarted;
          std::thread* ioThread;


          friend void ioThreadFunc(NetworkClient* client);
        };

      }
    }
  }
}



#endif