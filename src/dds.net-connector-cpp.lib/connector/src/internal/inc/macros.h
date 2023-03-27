#ifndef DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_MACROS_H_
#define DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_MACROS_H_


#include <chrono>
#include <thread>


#define SLEEP_MS(ms)     std::this_thread::sleep_for(std::chrono::milliseconds(100))
#define SLEEP(msec)      SLEEP_MS(msec)
#define sleep(msec)      SLEEP(msec)







#endif