#include <iostream>
#include <string>
#include <exception>

#include <stdio.h>

#include "ddsconnector.h"

using namespace std;
using namespace dds::net::connector;


void wait_for_exit_key();

void circle_values_consumer(string& variableName, double variableValue);

string test_string_producer(string& variableName);
bool test_boolean_producer(string& variableName);
char test_byte_producer(string& variableName);
short test_word_producer(string& variableName);
long test_dword_producer(string& variableName);
long long test_qword_producer(string& variableName);
unsigned char test_unsigned_byte_producer(string& variableName);
unsigned short test_unsigned_word_producer(string& variableName);
unsigned long test_unsigned_dword_producer(string& variableName);
unsigned long long test_unsigned_qword_producer(string& variableName);
float test_single_producer(string& variableName);
double test_double_producer(string& variableName);


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

    connector.registerDoubleConsumer("Circle-X", circle_values_consumer, ON_CHANGE);
    connector.registerDoubleConsumer("Circle-Y", circle_values_consumer, ON_CHANGE);

    connector.registerStringProvider("Test-String", test_string_producer, ON_CHANGE);
    connector.registerBooleanProvider("Test-Boolean", test_boolean_producer, ON_CHANGE);
    connector.registerByteProvider("Test-Byte", test_byte_producer, ON_CHANGE);
    connector.registerWordProvider("Test-Word", test_word_producer, ON_CHANGE);
    connector.registerDWordProvider("Test-DWord", test_dword_producer, ON_CHANGE);
    connector.registerQWordProvider("Test-QWord", test_qword_producer, ON_CHANGE);
    connector.registerUnsignedByteProvider("Test-UnsignedByte", test_unsigned_byte_producer, ON_CHANGE);
    connector.registerUnsignedWordProvider("Test-UnsignedWord", test_unsigned_word_producer, ON_CHANGE);
    connector.registerUnsignedDWordProvider("Test-UnsignedDWord", test_unsigned_dword_producer, ON_CHANGE);
    connector.registerUnsignedQWordProvider("Test-UnsignedQWord", test_unsigned_qword_producer, ON_CHANGE);
    connector.registerSingleProvider("Test-Single", test_single_producer, ON_CHANGE);
    connector.registerDoubleProvider("Test-Double", test_double_producer, ON_CHANGE);

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

void circle_values_consumer(string& variableName, double variableValue)
{
  if (variableName == "Circle-X")
  {
    x = variableValue;
  }
  else if (variableName == "Circle-Y")
  {
    y = variableValue;

    cout << x << ", " << y << endl;
  }
}



bool test_boolean = false;
double test_value = -100.5;

string test_string_producer(string& variableName)
{
  string s = "Test Value = ";
  s += to_string(test_value);
  return s;
}
bool test_boolean_producer(string& variableName)
{
  test_boolean != test_boolean;
  return test_boolean;
}
char test_byte_producer(string& variableName)
{
  return (char)test_value;
}
short test_word_producer(string& variableName)
{
  return (short)test_value;
}
long test_dword_producer(string& variableName)
{
  return (long)test_value;
}
long long test_qword_producer(string& variableName)
{
  return (long long)test_value;
}
unsigned char test_unsigned_byte_producer(string& variableName)
{
  return (unsigned char)test_value;
}
unsigned short test_unsigned_word_producer(string& variableName)
{
  return (unsigned short)test_value;
}
unsigned long test_unsigned_dword_producer(string& variableName)
{
  return (unsigned long)test_value;
}
unsigned long long test_unsigned_qword_producer(string& variableName)
{
  return (unsigned long long)test_value;
}
float test_single_producer(string& variableName)
{
  return (float)test_value;
}
double test_double_producer(string& variableName)
{
  if (test_value <= -100.0)
  {
    test_value = 100.5;
  }
  else
  {
    test_value = -100.5;
  }

  return test_value;
}



