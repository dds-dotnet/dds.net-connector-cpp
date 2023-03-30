#ifndef DDS_DOT_NET_CONNECTOR_INC_ERROR_H_
#define DDS_DOT_NET_CONNECTOR_INC_ERROR_H_


#include <exception>


namespace dds {
  namespace net {
    namespace connector {

      class Error : std::exception {
      public:
        Error(const char* message)
        {
          this->message = message;
        }

#if TARGET_PLATFORM == PLATFORM_WINDOWS
        virtual char const* what() const
#else
        virtual const char* what() const
#endif
        {
          return message != nullptr ? message : "Unknown exception";
        }

      private:
        const char* message;
      };
    }
  }
}




#endif