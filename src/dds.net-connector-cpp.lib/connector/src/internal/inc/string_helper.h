#ifndef DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_STRING_HELPER_H_
#define DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_STRING_HELPER_H_

#include <string>


namespace dds {
  namespace net {
    namespace connector {
      namespace _internal {

        class StringHelper {
        public:
          static bool isValidIPv4Address(std::string& address);
          static std::string removeSpaces(std::string& inp);
        };

      }
    }
  }
}



#endif