#include "src/internal/inc/sync_queue.h"

#include "src/internal/inc/macros.h"

#include <memory.h>
#include <exception>


static const int SLEEP_TIME_MS_WHEN_DATA_CANNOT_BE_DEQUEUED = 5;
static const int SLEEP_TIME_MS_WHEN_DATA_CANNOT_BE_ENQUEUED = 5;


template <typename T>
dds::net::connector::_internal::SyncQueue<T>::SyncQueue(int queueSize)
{
  this->queueSize = queueSize;

  if (queueSize <= 0) {
    throw std::exception("Invalid queue size - the size must be a positive number");
  }

  queue = new T[queueSize];
  queueValidity = new bool[queueSize];

  nextWriteIndex = 0;
  nextReadIndex = 0;
}

template<typename T>
bool dds::net::connector::_internal::SyncQueue<T>::canDequeue()
{
  bool ret = false;

  lock.lock();

  ret = queueValidity[nextReadIndex];

  lock.unlock();

  return ret;
}

template<typename T>
T dds::net::connector::_internal::SyncQueue<T>::dequeue()
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
    
    sleep(SLEEP_TIME_MS_WHEN_DATA_CANNOT_BE_DEQUEUED);
  }
}

template<typename T>
bool dds::net::connector::_internal::SyncQueue<T>::canEnqueue()
{
  return false;
}

template<typename T>
void dds::net::connector::_internal::SyncQueue<T>::enqueue(T data)
{
}
