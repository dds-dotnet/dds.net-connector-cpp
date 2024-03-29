#ifndef DDS_DOT_NET_CONNECTOR_INC_LOGGER_H_
#define DDS_DOT_NET_CONNECTOR_INC_LOGGER_H_

#include <mutex>


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

        virtual void info(const char* messageLine) = 0;
        virtual void warning(const char* messageLine) = 0;
        virtual void error(const char* messageLine) = 0;
      };



      class BlankLogger : public Logger {
      public:
        void info(const char* messageLine) override {}
        void warning(const char* messageLine) override {}
        void error(const char* messageLine) override {}
      };



      class ConsoleLogger : public Logger {
      public:
        ConsoleLogger(LogLevel logLevel = Logger::LOG_LEVEL_INFORMATION);
        
        void info(const char* message) override;
        void warning(const char* message) override;
        void error(const char* message) override;

      private:
        std::mutex lock;
        LogLevel logLevel;
      };

    } // namespace connector

  } // namespace net

} // namespace dds



#endif