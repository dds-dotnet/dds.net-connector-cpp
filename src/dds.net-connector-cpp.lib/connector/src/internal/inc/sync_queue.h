#ifndef DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_SYNC_QUEUE_H_
#define DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_SYNC_QUEUE_H_

#include "src/internal/inc/sync_queue_reader.h"
#include "src/internal/inc/sync_queue_writer.h"


namespace dds {
  namespace net {
    namespace connector {
      namespace _internal {

        template <typename T>
        class SyncQueue : public SyncQueueReader<T>, public SyncQueueWriter<T> {

        public:
          SyncQueue(int queueSize = 100);

          bool canDequeue() override;
          T dequeue() override;
          bool canEnqueue() override;
          void enqueue(T data) override;


        private:
          int queueSize;
        };

      }
    }
  }
}



#endif