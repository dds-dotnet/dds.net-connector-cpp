#ifndef DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_EASY_THREAD_H_
#define DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_EASY_THREAD_H_


namespace dds {
  namespace net {
    namespace connector {
      namespace _internal {

        typedef bool(*ThreadWork)(void* obj);

        class EasyThread {
        public:

          EasyThread(ThreadWork, void* obj);
          EasyThread(ThreadWork, void* obj, int periodicity);

          void start();
          void stop();
        };

      }
    }
  }
}



#endif