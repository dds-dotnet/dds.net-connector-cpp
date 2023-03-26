#ifndef DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_SYNC_QUEUE_READER_H_
#define DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_SYNC_QUEUE_READER_H_


namespace dds {
  namespace net {
    namespace connector {
      namespace _internal {

        template <class T>
        class SyncQueueReader {

        public:
          virtual bool canDequeue() = 0;
          virtual T dequeue() = 0;
        };

      }
    }
  }
}



#endif