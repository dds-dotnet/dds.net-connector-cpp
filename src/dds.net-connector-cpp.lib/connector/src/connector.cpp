#include "inc/connector.h"


std::string dds::net::connector::Connector::getLibraryVersion()
{
  return "1.0.0";
}

std::string dds::net::connector::Connector::getApplicationName()
{
  return this->applicationName;
}

std::string dds::net::connector::Connector::getServerAddressIPv4()
{
  return this->serverAddressIPv4;
}
