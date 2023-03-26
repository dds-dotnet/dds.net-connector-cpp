#ifndef DDS_DOT_NET_CONNECTOR_INC_LOGGER_H_
#define DDS_DOT_NET_CONNECTOR_INC_LOGGER_H_


namespace dds {
  namespace net {
    namespace connector {

      class Logger {
      public:
        enum LogLevel {
          LOG_LEVEL_INFORMATION,
          LOG_LEVEL_WARNING,
          LOG_LEVEL_ERROR
        };

        virtual void logInformation(const char* messageLine) = 0;
        virtual void logWarning(const char* messageLine) = 0;
        virtual void logError(const char* messageLine) = 0;
      };

      class BlankLogger : Logger {
      public:
        void logInformation(const char* messageLine) override {}
        void logWarning(const char* messageLine) override {}
        void logError(const char* messageLine) override {}
      };

    }
  }
}



#endif