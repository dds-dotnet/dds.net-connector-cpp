#include <iostream>
#include <string>
#include <exception>

#include "ddsconnector.h"
#include "logger.h"

using namespace std;
using namespace dds::net::connector;


int main()
{
    std::cout << "DDS.Net Connected App!\n";

    string appName = "My CPP App";
    string serverIP = "127.0.0.1";
    unsigned short serverPort = 44556;

    try
    {
      DdsConnector* connector = new DdsConnector(appName, serverIP, serverPort, new ConsoleLogger());
    }
    catch (std::exception& ex)
    {
      std::cout << "Initialization ERROR! " << ex.what() << std::endl;
    }
}
