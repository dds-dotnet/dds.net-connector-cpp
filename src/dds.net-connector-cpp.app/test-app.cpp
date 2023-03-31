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
    cout << "DDS.Net Connected App!" << endl;
    cout << "======================" << endl;
    cout << "Press Ctrl+C to exit." << endl << endl;

    string appName = "My CPP App";
    string serverIP = "127.0.0.1";
    unsigned short serverPort = 44556;

    try
    {
      DdsConnector* connector =
        new DdsConnector(
          appName,
          serverIP, serverPort, new ConsoleLogger());
    }
    catch (exception& ex)
    {
      cout << "Exception! " << ex.what() << endl;
    }

    wait_for_exit_key();

    cout << endl << endl << endl;
}

void wait_for_exit_key()
{
  char ch;
  while ((ch = getc(stdin)) != 122);
}