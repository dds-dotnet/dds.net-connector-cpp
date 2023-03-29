#include "src/internal/inc/string_helper.h"

#include <regex>


static std::regex ipv4("\\s*(\\d{1,3})\\s*\\.\\s*(\\d{1,3})\\s*\\.\\s*(\\d{1,3})\\s*\\.\\s*(\\d{1,3})\\s*");
static std::regex spaces("\\s+");


bool dds::net::connector::_internal::StringHelper::isValidIPv4Address(std::string& address)
{
  return std::regex_match(address, ipv4);
}

std::string dds::net::connector::_internal::StringHelper::removeSpaces(std::string& inp)
{
  return std::regex_replace(inp, spaces, "");
}
