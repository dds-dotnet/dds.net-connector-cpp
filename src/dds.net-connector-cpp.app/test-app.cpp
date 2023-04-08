#include <iostream>
#include <string>
#include <exception>

#include <stdio.h>

#include "ddsconnector.h"

using namespace std;
using namespace dds::net::connector;


void wait_for_exit_key();
void my_double_consumer(std::string& variableName, double variableValue);


int main()
{
  string appName = "DDS.Net C++ Connected App";
  string serverIP = "127.0.0.1";
  unsigned short serverPort = 44556;

  cout << appName << endl;
  cout << "-----" << endl;
  cout << "Press Ctrl+C / input 'C' to exit." << endl << endl;

  try
  {
    DdsConnector connector(
        appName,
        serverIP, serverPort,
        new ConsoleLogger());

    connector.registerDoubleConsumer("TESTX", my_double_consumer, ON_CHANGE);
    connector.registerDoubleConsumer("TESTY", my_double_consumer, ON_CHANGE);

    connector.start();

    wait_for_exit_key();

    connector.stop();
  }
  catch (exception& ex)
  {
    cout << "Error! " << ex.what() << endl;
  }

  cout << endl << endl << endl;
}


void wait_for_exit_key()
{
  char ch;
  while ((ch = getc(stdin)) != 'C');
}


static double x, y;

void my_double_consumer(std::string& variableName, double variableValue)
{
  if (variableName == "TESTX")
  {
    x = variableValue;
  }
  else if (variableName == "TESTY")
  {
    y = variableValue;

    cout << x << ", " << y << endl;
  }
}

