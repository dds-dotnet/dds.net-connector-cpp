#ifndef DDS_DOT_NET_CONNECTOR_INC_TYPES_H_
#define DDS_DOT_NET_CONNECTOR_INC_TYPES_H_

#include <string>


typedef unsigned short ushort;


//- 
//- Provider functions
//- 
typedef std::string (*StringProvider)(const std::string& variableName);

typedef bool (*BooleanProvider)(const std::string& variableName);

typedef char (*ByteProvider)(const std::string& variableName);
typedef short (*WordProvider)(const std::string& variableName);
typedef long (*DWordProvider)(const std::string& variableName);
typedef long long (*QWordProvider)(const std::string& variableName);

typedef unsigned char (*UnsignedByteProvider)(const std::string& variableName);
typedef unsigned short (*UnsignedWordProvider)(const std::string& variableName);
typedef unsigned long (*UnsignedDWordProvider)(const std::string& variableName);
typedef unsigned long long (*UnsignedQWordProvider)(const std::string& variableName);

typedef float (*SingleProvider)(const std::string& variableName);
typedef double (*DoubleProvider)(const std::string& variableName);

typedef int (*RawBytesProvider)(const std::string& variableName, unsigned char* buffer, int bufferSize);


//- 
//- Consumer functions
//- 
typedef void (*StringConsumer)(const std::string& variableName, const std::string& variableValue);

typedef void (*BooleanConsumer)(const std::string& variableName, bool variableValue);

typedef void (*ByteConsumer)(const std::string& variableName, char variableValue);
typedef void (*WordConsumer)(const std::string& variableName, short variableValue);
typedef void (*DWordConsumer)(const std::string& variableName, long variableValue);
typedef void (*QWordConsumer)(const std::string& variableName, long long variableValue);

typedef void (*UnsignedByteConsumer)(const std::string& variableName, unsigned char variableValue);
typedef void (*UnsignedWordConsumer)(const std::string& variableName, unsigned short variableValue);
typedef void (*UnsignedDWordConsumer)(const std::string& variableName, unsigned long variableValue);
typedef void (*UnsignedQWordConsumer)(const std::string& variableName, unsigned long long variableValue);

typedef void (*SingleConsumer)(const std::string& variableName, float variableValue);
typedef void (*DoubleConsumer)(const std::string& variableName, double variableValue);

typedef void (*RawBytesConsumer)(const std::string& variableName, unsigned char* buffer, int dataSize);


typedef enum {
  ON_CHANGE = 0,  // Updates only when the value is changed
  HIGHEST,        // Updates every BASE_TIME_SLOT_MSEC x 1 msec
  HIGH,           // Updates every BASE_TIME_SLOT_MSEC x 2 msec
  NORMAL,         // Updates every BASE_TIME_SLOT_MSEC x 4 msec
  LOW,            // Updates every BASE_TIME_SLOT_MSEC x 8 msec
  LOWEST          // Updates every BASE_TIME_SLOT_MSEC x 16 msec
} Periodicity;


#endif
