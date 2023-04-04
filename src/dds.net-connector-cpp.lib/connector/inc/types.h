#ifndef DDS_DOT_NET_CONNECTOR_INC_TYPES_H_
#define DDS_DOT_NET_CONNECTOR_INC_TYPES_H_

#include <string>


typedef unsigned short ushort;


//- 
//- Provider functions
//- 
typedef std::string (*StringProvider)(std::string& variableName);

typedef bool (*BooleanProvider)(std::string& variableName);

typedef char (*ByteProvider)(std::string& variableName);
typedef short (*WordProvider)(std::string& variableName);
typedef long (*DWordProvider)(std::string& variableName);
typedef long long (*QWordProvider)(std::string& variableName);

typedef unsigned char (*UnsignedByteProvider)(std::string& variableName);
typedef unsigned short (*UnsignedWordProvider)(std::string& variableName);
typedef unsigned long (*UnsignedDWordProvider)(std::string& variableName);
typedef unsigned long long (*UnsignedQWordProvider)(std::string& variableName);

typedef float (*SingleProvider)(std::string& variableName);
typedef double (*DoubleProvider)(std::string& variableName);

typedef int (*RawBytesProvider)(std::string& variableName, unsigned char* buffer, int bufferSize);


//- 
//- Consumer functions
//- 
typedef void (*StringConsumer)(std::string& variableName, std::string& variableValue);

typedef void (*BooleanConsumer)(std::string& variableName, bool variableValue);

typedef void (*ByteConsumer)(std::string& variableName, char variableValue);
typedef void (*WordConsumer)(std::string& variableName, short variableValue);
typedef void (*DWordConsumer)(std::string& variableName, long variableValue);
typedef void (*QWordConsumer)(std::string& variableName, long long variableValue);

typedef void (*UnsignedByteConsumer)(std::string& variableName, unsigned char variableValue);
typedef void (*UnsignedWordConsumer)(std::string& variableName, unsigned short variableValue);
typedef void (*UnsignedDWordConsumer)(std::string& variableName, unsigned long variableValue);
typedef void (*UnsignedQWordConsumer)(std::string& variableName, unsigned long long variableValue);

typedef void (*SingleConsumer)(std::string& variableName, float variableValue);
typedef void (*DoubleConsumer)(std::string& variableName, double variableValue);

typedef void (*RawBytesConsumer)(std::string& variableName, unsigned char* buffer, int bufferSize, int effectiveBytes);


typedef enum {
  ON_CHANGE = 0,  // Updates only when the value is changed
  HIGHEST,        // Updates every BASE_TIME_SLOT_MSEC x 1 msec
  HIGH,           // Updates every BASE_TIME_SLOT_MSEC x 2 msec
  NORMAL,         // Updates every BASE_TIME_SLOT_MSEC x 4 msec
  LOW,            // Updates every BASE_TIME_SLOT_MSEC x 8 msec
  LOWEST          // Updates every BASE_TIME_SLOT_MSEC x 16 msec
} Periodicity;


#endif
