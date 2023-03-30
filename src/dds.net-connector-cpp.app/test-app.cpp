#include <iostream>
#include <string>
#include <exception>

#include <conio.h>

#include "ddsconnector.h"

using namespace std;
using namespace dds::net::connector;

void wait_for_exit_key();

int main()
{
    std::cout << "DDS.Net Connected App!" << std::endl;
    std::cout << "======================" << std::endl;

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
  std::cout << "Press ESC to exit." << std::endl;

  char ch;
  while ((ch = _getch()) != 27);
}