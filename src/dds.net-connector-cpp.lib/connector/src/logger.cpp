#include "inc/logger.h"

#include <iostream>


// **********************
// ConsoleLogger
// 
// ******************

dds::net::connector::ConsoleLogger::ConsoleLogger(LogLevel logLevel)
{
  this->logLevel = logLevel;
}

void dds::net::connector::ConsoleLogger::info(const char* message)
{
  if (message != nullptr && logLevel == Logger::LOG_LEVEL_INFORMATION)
  {
    lock.lock();
    std::cout << message << std::endl;
    lock.unlock();
  }
}

void dds::net::connector::ConsoleLogger::warning(const char* message)
{
  if (message != nullptr && logLevel != Logger::LOG_LEVEL_ERROR)
  {
    lock.lock();
    std::cout << "Warning: " << message << std::endl;
    lock.unlock();
  }
}

void dds::net::connector::ConsoleLogger::error(const char* message)
{
  lock.lock();
  std::cout << "Error: " << message << std::endl;
  lock.unlock();
}