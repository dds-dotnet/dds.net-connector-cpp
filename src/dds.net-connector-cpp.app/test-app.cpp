#include <iostream>
#include <string>
#include <exception>

#include <stdio.h>

#include "ddsconnector.h"

using namespace std;
using namespace dds::net::connector;

void wait_for_exit_key();

int main()
{
    std::cout << "DDS.Net Connected App!" << std::endl;
    std::cout << "======================" << std::endl;
    std::cout << "Press Ctrl+C to exit." << std::endl << std::endl;

    string appName = "My CPP App";
    string serverIP = "127.0.0.1";
    unsigned short serverPort = 44556;

    try
    {
      DdsConnector* connector = new DdsConnector(appName, serverIP, serverPort, new ConsoleLogger());
    }
    catch (std::exception& ex)
    {
      std::cout << "Exception! " << ex.what() << std::endl;
    }

    wait_for_exit_key();

    std::cout << std::endl << std::endl << std::endl;
}

void wait_for_exit_key()
{
  char ch;
  while ((ch = getc(stdin)) != 122);
}