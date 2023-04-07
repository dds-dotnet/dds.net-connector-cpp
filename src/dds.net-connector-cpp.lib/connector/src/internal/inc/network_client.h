#ifndef DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_NETWORK_CLIENT_H_
#define DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_NETWORK_CLIENT_H_

#include "src/internal/inc/threaded_network_client.h"

#include "inc/config.h"

#include <string>
#include <mutex>
#include <thread>


#if   TARGET_PLATFORM == PLATFORM_GNU_LINUX

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define socket_desc_t  int



#elif   TARGET_PLATFORM == PLATFORM_WINDOWS

#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <ws2def.h>
#include <fcntl.h>

#pragma comment(lib, "ws2_32.lib")

#define socket_desc_t SOCKET



#else

//- 



#endif


namespace dds {
  namespace net {
    namespace connector {
      class Logger;

      namespace _internal {

        class BufferManager;
        class NetworkClient;
        template<typename T> class SyncQueue;
        void ioThreadFunc(NetworkClient* client);



        class NetworkClient : public dds::net::connector::_internal::ThreadedNetworkClient {
        public:
          NetworkClient(
            Logger*,
            BufferManager*,
            int dataToServerQueueSize = 1000,
            int dataFromServerQueueSize = 1000);

          ~NetworkClient();

          virtual SyncQueueReader<PacketFromServer*>* getDataQueueFromServer() override;
          virtual SyncQueueWriter<PacketToServer*>* getDataQueueToServer() override;

          virtual void setCallbackOnConnectedWithServer(connectedCallback, void* obj) override;
          virtual void setCallbackOnDisconnectedFromServer(disconnectedCallback, void* obj) override;

          virtual void connect(std::string ipv4, unsigned short tcpPort) override;
          virtual void disconnect() override;

        private:
          Logger* logger;
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
          bool isConnected;
          socket_desc_t socketFileDescriptor;
          sockaddr_in targetSocketAddress;

          bool isIOThreadStarted;
          std::thread* ioThread;


          friend void ioThreadFunc(NetworkClient* client);
        };

      }
    }
  }
}



#endif