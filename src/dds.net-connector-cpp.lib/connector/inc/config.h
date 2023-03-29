#ifndef DDS_DOT_NET_CONNECTOR_INC_CONFIG_H_
#define DDS_DOT_NET_CONNECTOR_INC_CONFIG_H_


#define LIBRARY_VERSION            "1.0.0"
#define BASE_TIME_SLOT_MSEC        50

#define PLATFORM_GNU_LINUX              0x00010000
#define PLATFORM_MAC_OS                 0x00020000
#define PLATFORM_WINDOWS                0x00040000

#ifndef TARGET_PLATFORM
  #define   TARGET_PLATFORM        PLATFORM_GNU_LINUX
#endif



#endif