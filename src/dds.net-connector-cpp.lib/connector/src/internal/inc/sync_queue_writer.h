#ifndef DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_SYNC_QUEUE_WRITER_H_
#define DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_SYNC_QUEUE_WRITER_H_


namespace dds {
  namespace net {
    namespace connector {
      namespace _internal {

        template <typename T>
        class SyncQueueWriter {

        public:
          virtual bool canEnqueue() = 0;
          virtual void enqueue(T data) = 0;
        };

      }
    }
  }
}



#endif