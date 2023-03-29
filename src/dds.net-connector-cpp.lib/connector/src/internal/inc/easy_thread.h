#ifndef DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_EASY_THREAD_H_
#define DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_EASY_THREAD_H_

#include <thread>
#include <atomic>
#include <mutex>


namespace dds {
  namespace net {
    namespace connector {
      namespace _internal {

        class EasyThread;

        typedef bool(*ThreadWork)(void* obj);
        void continuousThreadFunction(EasyThread*);
        void periodicThreadFunction(EasyThread*);

        class EasyThread {
        public:

          EasyThread(ThreadWork threadWork, void* threadWorkObj);
          EasyThread(ThreadWork threadWork, void* threadWorkObj, int periodicity);

          void start();
          void stop();


        private:
          ThreadWork threadWork;
          void* threadWorkObj;
          int periodicity;

          std::mutex threadLock;
          std::thread* thread;
          std::atomic<bool> isThreadRunning;

          friend void continuousThreadFunction(EasyThread*);
          friend void periodicThreadFunction(EasyThread*);
        };

      }
    }
  }
}



#endif