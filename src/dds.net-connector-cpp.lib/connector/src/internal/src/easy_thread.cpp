#include "src/internal/inc/easy_thread.h"

#include <exception>


dds::net::connector::_internal::EasyThread::EasyThread(ThreadWork threadWork, void* threadWorkObj)
{
  this->threadWork = threadWork;
  this->threadWorkObj = threadWorkObj;
  this->periodicity = -1;

  if (threadWork == nullptr)
  {
    throw std::exception("The thread-work function is not provided.");
  }
}

dds::net::connector::_internal::EasyThread::EasyThread(ThreadWork threadWork, void* threadWorkObj, int periodicity)
{
  this->threadWork = threadWork;
  this->threadWorkObj = threadWorkObj;
  this->periodicity = periodicity;

  if (threadWork == nullptr)
  {
    throw std::exception("The thread-work function is not provided.");
  }

  if (periodicity <= 0)
  {
    throw std::exception("Invalid periodicity value for invoking the thread-work function.");
  }
}

void dds::net::connector::_internal::EasyThread::start()
{
}

void dds::net::connector::_internal::EasyThread::stop()
{
}
