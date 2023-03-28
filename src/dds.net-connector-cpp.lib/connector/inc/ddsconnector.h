#ifndef DDS_DOT_NET_CONNECTOR_INC_DDSCONNECTOR_H_
#define DDS_DOT_NET_CONNECTOR_INC_DDSCONNECTOR_H_

#include "config.h"
#include "types.h"

#include <string>
#include <mutex>
#include <map>



namespace dds {
  namespace net {
    namespace connector {
      class Logger;

      namespace _internal {
        class ThreadedNetworkClient;
        class PacketFromServer;
        class PacketToServer;
        class EasyThread;
        template<typename T> class SyncQueueReader;
        template<typename T> class SyncQueueWriter;

        namespace variable {
          class BaseVariable;
        }
      }
    }
  }
}

namespace dds {
  namespace net {
    namespace connector {

      static void onConnectedWithServer(void* connector);
      static void onDisconnectedFromServer(void* connector);
      static bool dataReceptionWorker(void* connector);
      static bool periodicUpdateWorker(void* connector);

      class DdsConnector {
      public:
        DdsConnector(
          std::string applicationName,
          std::string serverIPv4, ushort serverPortTCP,
          Logger* logger = nullptr);

        void start();
        void stop();

        static std::string getLibraryVersion();

        std::string getApplicationName();
        std::string getServerAddressIPv4();
        ushort getServerPortTCP();

        //- 
        //- Providers
        //- 
        void registerStringProvider(std::string variableName, stringProviderFunc provider, Periodicity periodicity);
        void registerBooleanProvider(std::string variableName, booleanProviderFunc provider, Periodicity periodicity);
        void registerByteProvider(std::string variableName, byteProviderFunc provider, Periodicity periodicity);
        void registerWordProvider(std::string variableName, wordProviderFunc provider, Periodicity periodicity);
        void registerDWordProvider(std::string variableName, dWordProviderFunc provider, Periodicity periodicity);
        void registerQWordProvider(std::string variableName, qWordProviderFunc provider, Periodicity periodicity);
        void registerUnsignedByteProvider(std::string variableName, unsignedByteProviderFunc provider, Periodicity periodicity);
        void registerUnsignedWordProvider(std::string variableName, unsignedWordProviderFunc provider, Periodicity periodicity);
        void registerUnsignedDWordProvider(std::string variableName, unsignedDWordProviderFunc provider, Periodicity periodicity);
        void registerUnsignedQWordProvider(std::string variableName, unsignedQWordProviderFunc provider, Periodicity periodicity);
        void registerSingleProvider(std::string variableName, singleProviderFunc provider, Periodicity periodicity);
        void registerDoubleProvider(std::string variableName, doubleProviderFunc provider, Periodicity periodicity);
        void registerRawBytesProvider(std::string variableName, rawBytesProviderFunc provider, Periodicity periodicity);

        void unregisterProvider(std::string variableName);
        
        //- 
        //- Consumers
        //- 
        void registerStringConsumer(std::string variableName, stringConsumerFunc consumer, Periodicity periodicity);
        void registerBooleanConsumer(std::string variableName, booleanConsumerFunc consumer, Periodicity periodicity);
        void registerByteConsumer(std::string variableName, byteConsumerFunc consumer, Periodicity periodicity);
        void registerWordConsumer(std::string variableName, wordConsumerFunc consumer, Periodicity periodicity);
        void registerDWordConsumer(std::string variableName, dWordConsumerFunc consumer, Periodicity periodicity);
        void registerQWordConsumer(std::string variableName, qWordConsumerFunc consumer, Periodicity periodicity);
        void registerUnsignedByteConsumer(std::string variableName, unsignedByteConsumerFunc consumer, Periodicity periodicity);
        void registerUnsignedWordConsumer(std::string variableName, unsignedWordConsumerFunc consumer, Periodicity periodicity);
        void registerUnsignedDWordConsumer(std::string variableName, unsignedDWordConsumerFunc consumer, Periodicity periodicity);
        void registerUnsignedQWordConsumer(std::string variableName, unsignedQWordConsumerFunc consumer, Periodicity periodicity);
        void registerSingleConsumer(std::string variableName, singleConsumerFunc consumer, Periodicity periodicity);
        void registerDoubleConsumer(std::string variableName, doubleConsumerFunc consumer, Periodicity periodicity);
        void registerRawBytesConsumer(std::string variableName, rawBytesConsumerFunc consumer, Periodicity periodicity);

        void unregisterConsumer(std::string variableName);



      private:
        std::string applicationName;
        std::string serverAddressIPv4;
        ushort serverPortTCP;

        Logger* logger;

        _internal::ThreadedNetworkClient* networkClient;
        _internal::SyncQueueReader<_internal::PacketFromServer*>* dataFromServer;
        _internal::SyncQueueWriter<_internal::PacketToServer*>* dataToServer;

        _internal::EasyThread* dataReceiverThread;
        _internal::EasyThread* periodicUpdateThread;

        int iterationCounter;

        std::mutex variablesMutex;

        std::map<std::string, _internal::variable::BaseVariable*> uploadVariables;
        std::map<std::string, _internal::variable::BaseVariable*> downloadVariables;

        std::map<std::string, _internal::variable::BaseVariable*> uploadVariablesToBeRegistered;
        std::map<std::string, _internal::variable::BaseVariable*> downloadVariablesToBeRegistered;

        friend void onConnectedWithServer(void* connector);
        friend void onDisconnectedFromServer(void* connector);
        friend bool dataReceptionWorker(void* connector);
        friend bool periodicUpdateWorker(void* connector);

      }; // class DdsConnector

    } // namespace connector

  } // namespace net

} // namespace dds

#endif