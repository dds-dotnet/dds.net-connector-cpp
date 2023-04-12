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

void test_string_consumer(const string& variableName, const string& variableValue);
void test_boolean_consumer(const string& variableName, bool variableValue);
void test_byte_consumer(const string& variableName, char variableValue);
void test_word_consumer(const string& variableName, short variableValue);
void test_dword_consumer(const string& variableName, long variableValue);
void test_qword_consumer(const string& variableName, long long variableValue);
void test_unsigned_byte_consumer(const string& variableName, unsigned char variableValue);
void test_unsigned_word_consumer(const string& variableName, unsigned short variableValue);
void test_unsigned_dword_consumer(const string& variableName, unsigned long variableValue);
void test_unsigned_qword_consumer(const string& variableName, unsigned long long variableValue);
void test_single_consumer(const string& variableName, float variableValue);
void test_double_consumer(const string& variableName, double variableValue);
void test_bytes_consumer(const string& variableName, unsigned char* buffer, int dataSize);


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
    connector.registerStringConsumer("Test-String", test_string_consumer, ON_CHANGE);
    connector.registerBooleanConsumer("Test-Boolean", test_boolean_consumer, ON_CHANGE);
    connector.registerByteConsumer("Test-Byte", test_byte_consumer, ON_CHANGE);
    connector.registerWordConsumer("Test-Word", test_word_consumer, ON_CHANGE);
    connector.registerDWordConsumer("Test-DWord", test_dword_consumer, ON_CHANGE);
    connector.registerQWordConsumer("Test-QWord", test_qword_consumer, ON_CHANGE);
    connector.registerUnsignedByteConsumer("Test-UnsignedByte", test_unsigned_byte_consumer, ON_CHANGE);
    connector.registerUnsignedWordConsumer("Test-UnsignedWord", test_unsigned_word_consumer, ON_CHANGE);
    connector.registerUnsignedDWordConsumer("Test-UnsignedDWord", test_unsigned_dword_consumer, ON_CHANGE);
    connector.registerUnsignedQWordConsumer("Test-UnsignedQWord", test_unsigned_qword_consumer, ON_CHANGE);
    connector.registerSingleConsumer("Test-Single", test_single_consumer, ON_CHANGE);
    connector.registerDoubleConsumer("Test-Double", test_double_consumer, ON_CHANGE);
    connector.registerRawBytesConsumer("Test-Bytes", test_bytes_consumer, ON_CHANGE);


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
  in_buff[1] = (unsigned char)test_value_unsigned + 1;
  in_buff[2] = (unsigned char)test_value_unsigned + 2;
  in_buff[3] = (unsigned char)test_value_unsigned + 3;
  in_buff[4] = (unsigned char)test_value_unsigned + 4;

  return 5;
}




void test_string_consumer(const string& variableName, const string& variableValue)
{
  cout << "Str: " << variableValue << endl;
}
void test_boolean_consumer(const string& variableName, bool variableValue)
{
  cout << "Bool: " << variableValue << endl;
}
void test_byte_consumer(const string& variableName, char variableValue)
{
  cout << "Byte: " << (int)variableValue << endl;
}
void test_word_consumer(const string& variableName, short variableValue)
{
  cout << "Word: " << (int)variableValue << endl;
}
void test_dword_consumer(const string& variableName, long variableValue)
{
  cout << "DWord: " << variableValue << endl;
}
void test_qword_consumer(const string& variableName, long long variableValue)
{
  cout << "QWord: " << variableValue << endl;
}
void test_unsigned_byte_consumer(const string& variableName, unsigned char variableValue)
{
  cout << "Unsigned Byte: " << (unsigned int)variableValue << endl;
}
void test_unsigned_word_consumer(const string& variableName, unsigned short variableValue)
{
  cout << "Unsigned Word: " << variableValue << endl;
}
void test_unsigned_dword_consumer(const string& variableName, unsigned long variableValue)
{
  cout << "Unsigned DWord: " << variableValue << endl;
}
void test_unsigned_qword_consumer(const string& variableName, unsigned long long variableValue)
{
  cout << "Unsigned QWord: " << variableValue << endl;
}
void test_single_consumer(const string& variableName, float variableValue)
{
  cout << "Single: " << variableValue << endl;
}
void test_double_consumer(const string& variableName, double variableValue)
{
  cout << "Double: " << variableValue << endl;
}
void test_bytes_consumer(const string& variableName, unsigned char* buffer, int dataSize)
{
  cout << "Raw Bytes: ";

  for (size_t i = 0; i < dataSize; i++)
  {
    cout << (int)buffer[i] << " ";
  }

  cout << endl;
}
