&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; <img src="./.assets/DDS.Net Connector Icon-CPP-BG-None.png" width="15%" />


# DDS.Net C++ Connector - v1.3.0

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


## Providers and Consumers

In this context, ***Providers*** are functions that provide data to the library for transferring to the target *DDS.Net Server* for onward sharing with corresponding consumers; and ***Consumers*** are functions that consume delivered data from connected *DDS.Net Server* through the library. Function signatures and their corresponding library registration functions are enlisted here.


### String

> Provider:

  * &nbsp; &nbsp;  Registration function: &nbsp; &nbsp;    dds::net::connector::DdsConnector::*registerStringProvider*
  * &nbsp; &nbsp;  Function signature: &nbsp; &nbsp;       ***std::string*** (\*provider)(const std::string& ***varName***)

> Consumer:

  * &nbsp; &nbsp;  Registration function: &nbsp; &nbsp;    dds::net::connector::DdsConnector::*registerStringConsumer*
  * &nbsp; &nbsp;  Function signature: &nbsp; &nbsp;       void (\*consumer)(const std::string& ***varName***, const std::string& ***value***)


### Boolean

> Provider:

  * &nbsp; &nbsp;  Registration function: &nbsp; &nbsp;    dds::net::connector::DdsConnector::*registerBooleanProvider*
  * &nbsp; &nbsp;  Function signature: &nbsp; &nbsp;       ***bool*** (\*provider)(const std::string& ***varName***)

> Consumer:

  * &nbsp; &nbsp;  Registration function: &nbsp; &nbsp;    dds::net::connector::DdsConnector::*registerBooleanConsumer*
  * &nbsp; &nbsp;  Function signature: &nbsp; &nbsp;       void (\*consumer)(const std::string& ***varName***, bool ***value***)


### Byte

> Provider:

  * &nbsp; &nbsp;  Registration function: &nbsp; &nbsp;    dds::net::connector::DdsConnector::*registerByteProvider*
  * &nbsp; &nbsp;  Function signature: &nbsp; &nbsp;       ***char*** (\*provider)(const std::string& ***varName***)

> Consumer:

  * &nbsp; &nbsp;  Registration function: &nbsp; &nbsp;    dds::net::connector::DdsConnector::*registerByteConsumer*
  * &nbsp; &nbsp;  Function signature: &nbsp; &nbsp;       void (\*consumer)(const std::string& ***varName***, char ***value***)


### Word

> Provider:

  * &nbsp; &nbsp;  Registration function: &nbsp; &nbsp;    dds::net::connector::DdsConnector::*registerWordProvider*
  * &nbsp; &nbsp;  Function signature: &nbsp; &nbsp;       ***short*** (\*provider)(const std::string& ***varName***)

> Consumer:

  * &nbsp; &nbsp;  Registration function: &nbsp; &nbsp;    dds::net::connector::DdsConnector::*registerWordConsumer*
  * &nbsp; &nbsp;  Function signature: &nbsp; &nbsp;       void (\*consumer)(const std::string& ***varName***, short ***value***)


### DWord

> Provider:

  * &nbsp; &nbsp;  Registration function: &nbsp; &nbsp;    dds::net::connector::DdsConnector::*registerDWordProvider*
  * &nbsp; &nbsp;  Function signature: &nbsp; &nbsp;       ***long*** (\*provider)(const std::string& ***varName***)

> Consumer:

  * &nbsp; &nbsp;  Registration function: &nbsp; &nbsp;    dds::net::connector::DdsConnector::*registerDWordConsumer*
  * &nbsp; &nbsp;  Function signature: &nbsp; &nbsp;       void (\*consumer)(const std::string& ***varName***, long ***value***)


### QWord

> Provider:

  * &nbsp; &nbsp;  Registration function: &nbsp; &nbsp;    dds::net::connector::DdsConnector::*registerQWordProvider*
  * &nbsp; &nbsp;  Function signature: &nbsp; &nbsp;       ***long long*** (\*provider)(const std::string& ***varName***)

> Consumer:

  * &nbsp; &nbsp;  Registration function: &nbsp; &nbsp;    dds::net::connector::DdsConnector::*registerQWordConsumer*
  * &nbsp; &nbsp;  Function signature: &nbsp; &nbsp;       void (\*consumer)(const std::string& ***varName***, long long ***value***)


### Unsigned Byte

> Provider:

  * &nbsp; &nbsp;  Registration function: &nbsp; &nbsp;    dds::net::connector::DdsConnector::*registerUnsignedByteProvider*
  * &nbsp; &nbsp;  Function signature: &nbsp; &nbsp;       ***unsigned char*** (\*provider)(const std::string& ***varName***)

> Consumer:

  * &nbsp; &nbsp;  Registration function: &nbsp; &nbsp;    dds::net::connector::DdsConnector::*registerUnsignedByteConsumer*
  * &nbsp; &nbsp;  Function signature: &nbsp; &nbsp;       void (\*consumer)(const std::string& ***varName***, unsigned char ***value***)


### Unsigned Word

> Provider:

  * &nbsp; &nbsp;  Registration function: &nbsp; &nbsp;    dds::net::connector::DdsConnector::*registerUnsignedWordProvider*
  * &nbsp; &nbsp;  Function signature: &nbsp; &nbsp;       ***unsigned short*** (\*provider)(const std::string& ***varName***)

> Consumer:

  * &nbsp; &nbsp;  Registration function: &nbsp; &nbsp;    dds::net::connector::DdsConnector::*registerUnsignedWordConsumer*
  * &nbsp; &nbsp;  Function signature: &nbsp; &nbsp;       void (\*consumer)(const std::string& ***varName***, unsigned short ***value***)


### Unsigned DWord

> Provider:

  * &nbsp; &nbsp;  Registration function: &nbsp; &nbsp;    dds::net::connector::DdsConnector::*registerUnsignedDWordProvider*
  * &nbsp; &nbsp;  Function signature: &nbsp; &nbsp;       ***unsigned long*** (\*provider)(const std::string& ***varName***)

> Consumer:

  * &nbsp; &nbsp;  Registration function: &nbsp; &nbsp;    dds::net::connector::DdsConnector::*registerUnsignedDWordConsumer*
  * &nbsp; &nbsp;  Function signature: &nbsp; &nbsp;       void (\*consumer)(const std::string& ***varName***, unsigned long ***value***)


### Unsigned QWord

> Provider:

  * &nbsp; &nbsp;  Registration function: &nbsp; &nbsp;    dds::net::connector::DdsConnector::*registerUnsignedQWordProvider*
  * &nbsp; &nbsp;  Function signature: &nbsp; &nbsp;       ***unsigned long long*** (\*provider)(const std::string& ***varName***)

> Consumer:

  * &nbsp; &nbsp;  Registration function: &nbsp; &nbsp;    dds::net::connector::DdsConnector::*registerUnsignedQWordConsumer*
  * &nbsp; &nbsp;  Function signature: &nbsp; &nbsp;       void (\*consumer)(const std::string& ***varName***, unsigned long long ***value***)


### Single

> Provider:

  * &nbsp; &nbsp;  Registration function: &nbsp; &nbsp;    dds::net::connector::DdsConnector::*registerSingleProvider*
  * &nbsp; &nbsp;  Function signature: &nbsp; &nbsp;       ***float*** (\*provider)(const std::string& ***varName***)

> Consumer:

  * &nbsp; &nbsp;  Registration function: &nbsp; &nbsp;    dds::net::connector::DdsConnector::*registerSingleConsumer*
  * &nbsp; &nbsp;  Function signature: &nbsp; &nbsp;       void (\*consumer)(const std::string& ***varName***, float ***value***)


### Double

> Provider:

  * &nbsp; &nbsp;  Registration function: &nbsp; &nbsp;    dds::net::connector::DdsConnector::*registerDoubleProvider*
  * &nbsp; &nbsp;  Function signature: &nbsp; &nbsp;       ***double*** (\*provider)(const std::string& ***varName***)

> Consumer:

  * &nbsp; &nbsp;  Registration function: &nbsp; &nbsp;    dds::net::connector::DdsConnector::*registerDoubleConsumer*
  * &nbsp; &nbsp;  Function signature: &nbsp; &nbsp;       void (\*consumer)(const std::string& ***varName***, double ***value***)


### Raw Bytes

> Provider:

  * &nbsp; &nbsp;  Registration function: &nbsp; &nbsp;    dds::net::connector::DdsConnector::*registerRawBytesProvider*
  * &nbsp; &nbsp;  Function signature: &nbsp; &nbsp;       ***int*** (\*provider)(const std::string& ***varName***, unsigned char\* ***in_buff***, int ***size***)

> Consumer:

  * &nbsp; &nbsp;  Registration function: &nbsp; &nbsp;    dds::net::connector::DdsConnector::*registerRawBytesConsumer*
  * &nbsp; &nbsp;  Function signature: &nbsp; &nbsp;       void (\*consumer)(const std::string& ***varName***, unsigned char\* ***in_buff***, int ***size***)






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
