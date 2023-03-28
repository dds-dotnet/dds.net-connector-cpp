#ifndef DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_INTERNAL_TYPES_H_
#define DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_INC_INTERNAL_TYPES_H_


typedef enum {
  HandShake = 0,                   // Initialization information / configuration exchange.
  VariablesRegistration = 1,       // Registering variables with the server.
  VariablesUpdateAtServer = 2,     // Updating variable values at the server.
  VariablesUpdateFromServer = 3,   // Updating variable values at the client.
  ErrorResponseFromServer = 4,     // Error response from the server.

  UnknownPacket // Unknown packet.
} PacketId;


typedef enum {
  Primitive = 0, // Represents the very basic variable type, e.g., string, integer, float, etc.
  RawBytes = 1,  // Represents a sequence of bytes (unsigned bytes).

  UnknownVariableType // Unknown type.
} VariableType;


typedef enum {
  String = 0,        // Represents a string of characters.
  Boolean = 1,       // Represents a boolean (True or False).
  Byte = 2,          // Represents a 1-byte Signed Integer.
  Word = 3,          // Represents a 2-byte Signed Integer.
  DWord = 4,         // Represents a 4-byte Signed Integer.
  QWord = 5,         // Represents an 8-byte Signed Integer.
  UnsignedByte = 6,  // Represents a 1-byte Unsigned Integer.
  UnsignedWord = 7,  // Represents a 2-byte Unsigned Integer.
  UnsignedDWord = 8, // Represents a 4-byte Unsigned Integer.
  UnsignedQWord = 9, // Represents an 8-byte Unsigned Integer.
  Single = 10,       // Represents a single precision 4-byte Floating-point number.
  Double = 11,       // Represents a double precision 8-byte Floating-point number.

  UnknownPrimitiveType // Unknown type.
} PrimitiveType;



#endif