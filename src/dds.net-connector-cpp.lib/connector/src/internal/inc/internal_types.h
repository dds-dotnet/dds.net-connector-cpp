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
  Primitive, // Represents the very basic variable type, e.g., string, integer, float, etc.
  RawBytes,  // Represents a sequence of bytes (unsigned bytes).

  UnknownVariableType // Unknown type.
} VariableType;



#endif