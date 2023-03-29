#ifndef DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_VARIABLES_ENC_DEC_HEADER_H_
#define DDS_DOT_NET_CONNECTOR_SRC_INTERNAL_VARIABLES_ENC_DEC_HEADER_H_


namespace dds {
  namespace net {
    namespace connector {
      namespace _internal {
        namespace variables {

          class EncDecHeader {

          public:
            static const int ID_SIZE_ON_BUFFER = sizeof(short);
            static const int VARIABLE_TYPE_SIZE_ON_BUFFER = 2;
          };
        }
      }
    }
  }
}

#endif
