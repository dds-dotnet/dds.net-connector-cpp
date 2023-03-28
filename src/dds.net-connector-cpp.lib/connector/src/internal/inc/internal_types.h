#ifndef DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_INTERNAL_TYPES_H_
#define DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_INTERNAL_TYPES_H_




typedef enum {
  HANDSHAKE = 0,                      // Initialization information / configuration exchange.
  VARIABLES_REGISTRATION = 1,         // Registering variables with the server.
  VARIABLES_UPDATE_AT_SERVER = 2,     // Updating variable values at the server.
  VARIABLES_UPDATE_FROM_SERVER = 3,   // Updating variable values at the client.
  ERROR_RESPONSE_FROM_SERVER = 4,     // Error response from the server.

  UNKNOWN_PACKET // Unknown packet.
} PacketId;


typedef enum {
  PRIMITIVE = 0,  // Represents the very basic variable type, e.g., string, integer, float, etc.
  RAW_BYTES = 1,  // Represents a sequence of bytes (unsigned bytes).

  UNKNOWN_VARIABLE_TYPE // Unknown type.
} VariableType;


typedef enum {
  STRING = 0,         // Represents a string of characters.
  BOOLEAN = 1,        // Represents a boolean (True or False).
  BYTE = 2,           // Represents a 1-byte Signed Integer.
  WORD = 3,           // Represents a 2-byte Signed Integer.
  DWORD = 4,          // Represents a 4-byte Signed Integer.
  QWORD = 5,          // Represents an 8-byte Signed Integer.
  UNSIGNED_BYTE = 6,  // Represents a 1-byte Unsigned Integer.
  UNSIGNED_WORD = 7,  // Represents a 2-byte Unsigned Integer.
  UNSIGNED_DWORD = 8, // Represents a 4-byte Unsigned Integer.
  UNSIGNED_QWORD = 9, // Represents an 8-byte Unsigned Integer.
  SINGLE = 10,        // Represents a single precision 4-byte Floating-point number.
  DOUBLE = 11,        // Represents a double precision 8-byte Floating-point number.

  UNKNOWN_PRIMITIVE_TYPE // Unknown type.
} PrimitiveType;









#endif