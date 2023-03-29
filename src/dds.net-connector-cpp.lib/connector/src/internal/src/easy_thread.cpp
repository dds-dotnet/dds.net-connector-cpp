#include "src/internal/inc/easy_thread.h"

#include "src/internal/inc/macros.h"

#include <exception>

#define CONTINUOUS_THREAD_PERIODICITY              -1
#define SLEEP_TIME_WHEN_NOT_DONE_ANYTHING_MSEC     10


dds::net::connector::_internal::EasyThread::EasyThread(ThreadWork threadWork, void* threadWorkObj)
{
  this->threadWork = threadWork;
  this->threadWorkObj = threadWorkObj;
  this->periodicity = CONTINUOUS_THREAD_PERIODICITY;
  this->thread = nullptr;
  this->isThreadRunning = false;

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
  this->thread = nullptr;
  this->isThreadRunning = false;

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
  threadLock.lock();

  if (!isThreadRunning)
  {
    isThreadRunning = true;

    if (periodicity == CONTINUOUS_THREAD_PERIODICITY)
    {
      thread = new std::thread(continuousThreadFunction);
    }
    else
    {
      thread = new std::thread(periodicThreadFunction);
    }
  }

  threadLock.unlock();
}

void dds::net::connector::_internal::EasyThread::stop()
{
  threadLock.lock();

  if (isThreadRunning)
  {
    isThreadRunning = false;
    thread->join();
    thread = nullptr;
  }

  threadLock.unlock();
}

void dds::net::connector::_internal::EasyThread::continuousThreadFunction()
{
  while (isThreadRunning == true)
  {
    bool doneSomething = threadWork(threadWorkObj);

    if (doneSomething == false && isThreadRunning == true)
    {
      sleep(SLEEP_TIME_WHEN_NOT_DONE_ANYTHING_MSEC);
    }
  }
}

void dds::net::connector::_internal::EasyThread::periodicThreadFunction()
{
  while (isThreadRunning == true)
  {
    threadWork(threadWorkObj);

    if (isThreadRunning == true)
    {
      sleep(periodicity);
    }
  }
}
