#ifndef DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_INTERNAL_TYPES_H_
#define DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_INTERNAL_TYPES_H_




typedef enum {
  PACKET_ID_HANDSHAKE = 0,                      // Initialization information / configuration exchange.
  PACKET_ID_VARIABLES_REGISTRATION = 1,         // Registering variables with the server.
  PACKET_ID_VARIABLES_UPDATE_AT_SERVER = 2,     // Updating variable values at the server.
  PACKET_ID_VARIABLES_UPDATE_FROM_SERVER = 3,   // Updating variable values at the client.
  PACKET_ID_ERROR_RESPONSE_FROM_SERVER = 4,     // Error response from the server.
  PACKET_ID_UNKNOWN                             // Unknown packet.
} PacketId;


typedef enum {
  VARIABLE_TYPE_PRIMITIVE = 0,  // Represents the very basic variable type, e.g., string, integer, float, etc.
  VARIABLE_TYPE_RAW_BYTES = 1,  // Represents a sequence of bytes (unsigned bytes).
  VARIABLE_TYPE_UNKNOWN         // Unknown type.
} VariableType;


typedef enum {
  PRIMITIVE_TYPE_STRING = 0,           // Represents a string of characters.
  PRIMITIVE_TYPE_BOOLEAN = 1,          // Represents a boolean (True or False).
  PRIMITIVE_TYPE_BYTE = 2,             // Represents a 1-byte Signed Integer.
  PRIMITIVE_TYPE_WORD = 3,             // Represents a 2-byte Signed Integer.
  PRIMITIVE_TYPE_DWORD = 4,            // Represents a 4-byte Signed Integer.
  PRIMITIVE_TYPE_QWORD = 5,            // Represents an 8-byte Signed Integer.
  PRIMITIVE_TYPE_UNSIGNED_BYTE = 6,    // Represents a 1-byte Unsigned Integer.
  PRIMITIVE_TYPE_UNSIGNED_WORD = 7,    // Represents a 2-byte Unsigned Integer.
  PRIMITIVE_TYPE_UNSIGNED_DWORD = 8,   // Represents a 4-byte Unsigned Integer.
  PRIMITIVE_TYPE_UNSIGNED_QWORD = 9,   // Represents an 8-byte Unsigned Integer.
  PRIMITIVE_TYPE_SINGLE = 10,          // Represents a single precision 4-byte Floating-point number.
  PRIMITIVE_TYPE_DOUBLE = 11,          // Represents a double precision 8-byte Floating-point number.
  PRIMITIVE_TYPE_UNKNOWN               // Unknown type.
} PrimitiveType;

typedef char* BufferAddress;









#endif