#ifndef DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_SYNC_QUEUE_H_
#define DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_SYNC_QUEUE_H_

#include "inc/error.h"

#include "src/internal/inc/sync_queue_reader.h"
#include "src/internal/inc/sync_queue_writer.h"

#include "src/internal/inc/macros.h"

#include <mutex>

#include <memory.h>


#define SLEEP_TIME_MS_WHEN_DATA_CANNOT_BE_DEQUEUED     5
#define SLEEP_TIME_MS_WHEN_DATA_CANNOT_BE_ENQUEUED     5


namespace dds {
  namespace net {
    namespace connector {
      namespace _internal {

        template <typename T>
        class SyncQueue : public SyncQueueReader<T>, public SyncQueueWriter<T> {

        public:
          SyncQueue(int queueSize = 100)
          {
            this->queueSize = queueSize;

            if (queueSize <= 0)
            {
              throw Error("Invalid queue size - the size must be a positive number");
            }

            queue = new T[queueSize];
            queueValidity = new bool[queueSize];

            for (int i = 0; i < queueSize; i++)
            {
              queueValidity[i] = false;
            }

            nextWriteIndex = 0;
            nextReadIndex = 0;
          }

          bool canDequeue() override
          {
            bool ret = false;

            lock.lock();

            ret = queueValidity[nextReadIndex];

            lock.unlock();

            return ret;
          }
          T dequeue() override
          {
            while (true)
            {
              lock.lock();

              if (queueValidity[nextReadIndex] != false)
              {
                T data = queue[nextReadIndex];
                queueValidity[nextReadIndex] = false;

                nextReadIndex++;

                if (nextReadIndex == queueSize)
                {
                  nextReadIndex = 0;
                }

                lock.unlock();
                return data;
              }

              lock.unlock();

              sleep_msec(SLEEP_TIME_MS_WHEN_DATA_CANNOT_BE_DEQUEUED);
            }
          }
          
          bool canEnqueue() override
          {
            bool ret = false;

            lock.lock();

            ret = queueValidity[nextWriteIndex] == false;

            lock.unlock();

            return ret;
          }
          void enqueue(T data) override
          {
            while (true)
            {
              lock.lock();

              if (queueValidity[nextWriteIndex] == false)
              {
                queue[nextWriteIndex] = data;
                queueValidity[nextWriteIndex] = true;

                nextWriteIndex++;

                if (nextWriteIndex == queueSize)
                {
                  nextWriteIndex = 0;
                }

                lock.unlock();
                return;
              }

              lock.unlock();

              sleep_msec(SLEEP_TIME_MS_WHEN_DATA_CANNOT_BE_ENQUEUED);
            }
          }

          void clear()
          {
            lock.lock();

            for (int i = 0; i < queueSize; i++)
            {
              queueValidity[i] = false;
            }

            nextWriteIndex = 0;
            nextReadIndex = 0;

            lock.unlock();
          }


        private:
          std::mutex lock;

          int queueSize;
          T* queue;
          bool* queueValidity;

          int nextWriteIndex;
          int nextReadIndex;
        };

      }
    }
  }
}



#endif