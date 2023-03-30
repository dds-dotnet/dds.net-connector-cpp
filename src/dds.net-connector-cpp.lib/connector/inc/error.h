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

        virtual char const* what() const
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