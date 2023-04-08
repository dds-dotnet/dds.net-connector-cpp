&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; <img src="./.assets/DDS.Net Connector Icon-CPP-BG-None.png" width="15%" />


# DDS.Net C++ Connector - v1.0.0

*DDS.Net C++ Connector* intends to be a lightweight and performant connector for connecting distributed C++ applications through *DDS.Net Server*. The supported data types are:

| Main type                                          | Sub-type          | Represented data                                    |
|----------------------------------------------------|-------------------|-----------------------------------------------------|
| ***Primitive*** &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; | *String*          | Sequence of characters in Unicode                   |
|                                                    | *Boolean*         | A boolean (True or False)                           |
|                                                    | *Byte*            | 1-byte Signed Integer                               |
|                                                    | *Word*            | 2-byte Signed Integer                               |
|                                                    | *DWord*           | 4-byte Signed Integer                               |
|                                                    | *QWord*           | 8-byte Signed Integer                               |
|                                                    | *Unsigned Byte*   | 1-byte Unsigned Integer                             |
|                                                    | *Unsigned Word*   | 2-byte Unsigned Integer                             |
|                                                    | *Unsigned DWord*  | 4-byte Unsigned Integer                             |
|                                                    | *Unsigned QWord*  | 8-byte Unsigned Integer                             |
|                                                    | *Single*          | A single precision (4-byte) Floating-point number   |
|                                                    | *Double*          | A double precision (8-byte) Floating-point number   |
| ***Raw Bytes***                                    | -                 | Sequence of bytes                                   |

&nbsp;

> Data transfer with the server is only done when there is change in value

> Value subscribers are only invoked upon corresponding value changes

&nbsp;


## Sample application

Sample use of the library is done in following simple application:

```cpp
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

```
