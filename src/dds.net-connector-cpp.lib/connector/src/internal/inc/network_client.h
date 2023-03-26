#ifndef DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_NETWORK_CLIENT_H_
#define DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_NETWORK_CLIENT_H_

#include "src/internal/inc/threaded_network_client.h"


namespace dds {
  namespace net {
    namespace connector {
      namespace _internal {

        class NetworkClient : public dds::net::connector::_internal::ThreadedNetworkClient {
          virtual SyncQueueReader* getDataQueueFromServer() override;
          virtual SyncQueueWriter* getDataQueueToServer() override;

          virtual void setCallbackOnConnectedWithServer(connectedCallback) override;
          virtual void setCallbackOnDisconnectedFromServer(disconnectedCallback) override;
        };

      }
    }
  }
}



#endif