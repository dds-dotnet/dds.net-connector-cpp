#ifndef DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_EASY_THREAD_H_
#define DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_EASY_THREAD_H_


namespace dds {
  namespace net {
    namespace connector {
      namespace _internal {

        typedef bool(*unit_work_func)(void* obj);

        class EasyThread {
        public:

          EasyThread(unit_work_func, void* obj);
          EasyThread(unit_work_func, void* obj, int periodicity);

          void start();
          void stop();
        };

      }
    }
  }
}



#endif