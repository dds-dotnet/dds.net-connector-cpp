#include "src/internal/inc/string_helper.h"

#include <regex>


bool dds::net::connector::_internal::StringHelper::isValidIPv4Address(std::string& address)
{
  return false;
}

static std::regex spaces("\\s+");

std::string dds::net::connector::_internal::StringHelper::removeSpaces(std::string& inp)
{
  return std::regex_replace(inp, spaces, "");
}
