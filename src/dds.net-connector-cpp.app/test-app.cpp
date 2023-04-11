#include <iostream>
#include <string>
#include <exception>

#include <stdio.h>

#include "ddsconnector.h"

using namespace std;
using namespace dds::net::connector;


void wait_for_exit_key();

void circle_values_consumer(const string& variableName, double variableValue);

string test_string_producer(const string& variableName);
bool test_boolean_producer(const string& variableName);
char test_byte_producer(const string& variableName);
short test_word_producer(const string& variableName);
long test_dword_producer(const string& variableName);
long long test_qword_producer(const string& variableName);
unsigned char test_unsigned_byte_producer(const string& variableName);
unsigned short test_unsigned_word_producer(const string& variableName);
unsigned long test_unsigned_dword_producer(const string& variableName);
unsigned long long test_unsigned_qword_producer(const string& variableName);
float test_single_producer(const string& variableName);
double test_double_producer(const string& variableName);
int test_bytes_producer(const std::string& varName, unsigned char* in_buff, int size);


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

    connector.registerStringProvider("Test-String", test_string_producer, LOWEST);
    connector.registerBooleanProvider("Test-Boolean", test_boolean_producer, LOWEST);
    connector.registerByteProvider("Test-Byte", test_byte_producer, LOWEST);
    connector.registerWordProvider("Test-Word", test_word_producer, LOWEST);
    connector.registerDWordProvider("Test-DWord", test_dword_producer, LOWEST);
    connector.registerQWordProvider("Test-QWord", test_qword_producer, LOWEST);
    connector.registerUnsignedByteProvider("Test-UnsignedByte", test_unsigned_byte_producer, LOWEST);
    connector.registerUnsignedWordProvider("Test-UnsignedWord", test_unsigned_word_producer, LOWEST);
    connector.registerUnsignedDWordProvider("Test-UnsignedDWord", test_unsigned_dword_producer, LOWEST);
    connector.registerUnsignedQWordProvider("Test-UnsignedQWord", test_unsigned_qword_producer, LOWEST);
    connector.registerSingleProvider("Test-Single", test_single_producer, LOWEST);
    connector.registerDoubleProvider("Test-Double", test_double_producer, LOWEST);
    connector.registerRawBytesProvider("Test-Bytes", test_bytes_producer, LOWEST);

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

void circle_values_consumer(const string& variableName, double variableValue)
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
double test_value_signed = -100.555;
unsigned long long test_value_unsigned = 0;

string test_string_producer(const string& variableName)
{
  string s = "Test Value = ";
  s += to_string(test_value_signed);
  s += ", ";
  s += to_string(test_value_unsigned);
  return s;
}
bool test_boolean_producer(const string& variableName)
{
  test_boolean = !test_boolean;
  return test_boolean;
}
char test_byte_producer(const string& variableName)
{
  return (char)test_value_signed;
}
short test_word_producer(const string& variableName)
{
  return (short)test_value_signed;
}
long test_dword_producer(const string& variableName)
{
  return (long)test_value_signed;
}
long long test_qword_producer(const string& variableName)
{
  return (long long)test_value_signed;
}
unsigned char test_unsigned_byte_producer(const string& variableName)
{
  return (unsigned char)test_value_unsigned;
}
unsigned short test_unsigned_word_producer(const string& variableName)
{
  return (unsigned short)test_value_unsigned;
}
unsigned long test_unsigned_dword_producer(const string& variableName)
{
  return (unsigned long)test_value_unsigned;
}
unsigned long long test_unsigned_qword_producer(const string& variableName)
{
  return test_value_unsigned++;
}
float test_single_producer(const string& variableName)
{
  return (float)test_value_signed;
}
double test_double_producer(const string& variableName)
{
  if (test_value_signed <= -100.0)
  {
    test_value_signed = 100.555;
  }
  else
  {
    test_value_signed = -100.555;
  }

  return test_value_signed;
}
int test_bytes_producer(const std::string& varName, unsigned char* in_buff, int size)
{
  in_buff[0] = (unsigned char)test_value_unsigned;
  in_buff[1] = (unsigned char)test_value_unsigned;
  in_buff[2] = (unsigned char)test_value_unsigned;
  in_buff[3] = (unsigned char)test_value_unsigned;
  in_buff[4] = (unsigned char)test_value_unsigned;

  return 5;
}



