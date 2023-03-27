#include "src/internal/inc/sync_queue.h"


template <typename T>
dds::net::connector::_internal::SyncQueue<T>::SyncQueue(int queueSize)
{
  this->queueSize = queueSize;
}
