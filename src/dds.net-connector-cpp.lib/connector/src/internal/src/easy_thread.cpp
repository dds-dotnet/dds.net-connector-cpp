#include "src/internal/inc/easy_thread.h"

#include "inc/error.h"

#include "src/internal/inc/macros.h"

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
    throw Error("The thread-work function is not provided.");
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
    throw Error("The thread-work function is not provided.");
  }

  if (periodicity <= 0)
  {
    throw Error("Invalid periodicity value for invoking the thread-work function.");
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
      thread = new std::thread(continuousThreadFunction, this);
    }
    else
    {
      thread = new std::thread(periodicThreadFunction, this);
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

void dds::net::connector::_internal::continuousThreadFunction(EasyThread* th)
{
  while (th->isThreadRunning == true)
  {
    bool doneSomething = th->threadWork(th->threadWorkObj);

    if (doneSomething == false && th->isThreadRunning == true)
    {
      sleep_msec(SLEEP_TIME_WHEN_NOT_DONE_ANYTHING_MSEC);
    }
  }
}

void dds::net::connector::_internal::periodicThreadFunction(EasyThread* th)
{
  while (th->isThreadRunning == true)
  {
    th->threadWork(th->threadWorkObj);

    if (th->isThreadRunning == true)
    {
      sleep_msec(th->periodicity);
    }
  }
}
