#include <iostream>
#include <string>

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

    DdsConnector* connector = new DdsConnector(appName, serverIP, serverPort, new ConsoleLogger());
}
