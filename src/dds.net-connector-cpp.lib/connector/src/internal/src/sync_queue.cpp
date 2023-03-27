#include "src/internal/inc/sync_queue.h"

#include <exception>


template <typename T>
dds::net::connector::_internal::SyncQueue<T>::SyncQueue(int queueSize)
{
  this->queueSize = queueSize;

  if (queueSize <= 0) {
    throw std::exception("");
  }
}

template<typename T>
bool dds::net::connector::_internal::SyncQueue<T>::canDequeue()
{
  return false;
}

template<typename T>
T dds::net::connector::_internal::SyncQueue<T>::dequeue()
{
  return T();
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
