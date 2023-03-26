#ifndef DDS_DOT_NET_CONNECTOR_INC_TYPES_H_
#define DDS_DOT_NET_CONNECTOR_INC_TYPES_H_

#include <string>


typedef unsigned short ushort;

//- 
//- Provider functions
//- 
typedef std::string (*stringProviderFunc)(std::string variableName);

typedef bool (*booleanProviderFunc)(std::string variableName);

typedef char (*byteProviderFunc)(std::string variableName);
typedef short (*wordProviderFunc)(std::string variableName);
typedef long (*dWordProviderFunc)(std::string variableName);
typedef long long (*qWordProviderFunc)(std::string variableName);

typedef unsigned char (*unsignedByteProviderFunc)(std::string variableName);
typedef unsigned short (*unsignedWordProviderFunc)(std::string variableName);
typedef unsigned long (*unsignedDWordProviderFunc)(std::string variableName);
typedef unsigned long long (*unsignedQWordProviderFunc)(std::string variableName);

typedef float (*singleProviderFunc)(std::string variableName);
typedef double (*doubleProviderFunc)(std::string variableName);

typedef int (rawBytesProviderFunc)(std::string variableName, unsigned char* buffer, int bufferSize);

//- 
//- Consumer functions
//- 
typedef void (*stringConsumerFunc)(std::string variableName, std::string variableValue);

typedef void (*booleanConsumerFunc)(std::string variableName, bool variableValue);

typedef void (*byteConsumerFunc)(std::string variableName, char variableValue);
typedef void (*wordConsumerFunc)(std::string variableName, short variableValue);
typedef void (*dWordConsumerFunc)(std::string variableName, long variableValue);
typedef void (*qWordConsumerFunc)(std::string variableName, long long variableValue);

typedef void (*unsignedByteConsumerFunc)(std::string variableName, unsigned char variableValue);
typedef void (*unsignedWordConsumerFunc)(std::string variableName, unsigned short variableValue);
typedef void (*unsignedDWordConsumerFunc)(std::string variableName, unsigned long variableValue);
typedef void (*unsignedQWordConsumerFunc)(std::string variableName, unsigned long long variableValue);

typedef void (*singleConsumerFunc)(std::string variableName, float variableValue);
typedef void (*doubleConsumerFunc)(std::string variableName, double variableValue);

typedef void (*rawBytesConsumerFunc)(std::string variableName, unsigned char* buffer, int bufferSize, int effectiveBytes);


#endif
