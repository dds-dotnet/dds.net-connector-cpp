#ifndef DDS_DOT_NET_CONNECTOR_INC_DDSCONNECTOR_H_
#define DDS_DOT_NET_CONNECTOR_INC_DDSCONNECTOR_H_

#include "config.h"
#include "types.h"
#include "logger.h"

#include <string>
#include <mutex>
#include <list>
#include <map>



namespace dds {
  namespace net {
    namespace connector {

      namespace _internal {
        class BufferManager;
        class PacketPreprocessor;
        class ThreadedNetworkClient;
        class PacketFromServer;
        class PacketToServer;
        class EasyThread;
        template<typename T> class SyncQueueReader;
        template<typename T> class SyncQueueWriter;

        namespace variables {
          class BaseVariable;
        }
      }
    }
  }
}

namespace dds {
  namespace net {
    namespace connector {

      extern void onConnectedWithServer(void* connector);
      extern void onDisconnectedFromServer(void* connector);
      extern bool dataReceptionWorker(void* connector);
      extern bool periodicUpdateWorker(void* connector);

      class DdsConnector {
      public:
        DdsConnector(
          std::string applicationName,
          std::string serverIPv4, ushort serverPortTCP,
          Logger* logger = nullptr);

        ~DdsConnector();

        void start();
        void stop();

        static std::string getLibraryVersion();

        std::string getApplicationName();
        std::string getServerAddressIPv4();
        ushort getServerPortTCP();

        //- 
        //- Providers
        //- 
        void registerStringProvider(std::string variableName, StringProvider provider, Periodicity periodicity);
        void registerBooleanProvider(std::string variableName, BooleanProvider provider, Periodicity periodicity);
        void registerByteProvider(std::string variableName, ByteProvider provider, Periodicity periodicity);
        void registerWordProvider(std::string variableName, WordProvider provider, Periodicity periodicity);
        void registerDWordProvider(std::string variableName, DWordProvider provider, Periodicity periodicity);
        void registerQWordProvider(std::string variableName, QWordProvider provider, Periodicity periodicity);
        void registerUnsignedByteProvider(std::string variableName, UnsignedByteProvider provider, Periodicity periodicity);
        void registerUnsignedWordProvider(std::string variableName, UnsignedWordProvider provider, Periodicity periodicity);
        void registerUnsignedDWordProvider(std::string variableName, UnsignedDWordProvider provider, Periodicity periodicity);
        void registerUnsignedQWordProvider(std::string variableName, UnsignedQWordProvider provider, Periodicity periodicity);
        void registerSingleProvider(std::string variableName, SingleProvider provider, Periodicity periodicity);
        void registerDoubleProvider(std::string variableName, DoubleProvider provider, Periodicity periodicity);
        void registerRawBytesProvider(std::string variableName, RawBytesProvider provider, Periodicity periodicity);

        void unregisterProvider(std::string variableName);
        
        //- 
        //- Consumers
        //- 
        void registerStringConsumer(std::string variableName, StringConsumer consumer, Periodicity periodicity);
        void registerBooleanConsumer(std::string variableName, BooleanConsumer consumer, Periodicity periodicity);
        void registerByteConsumer(std::string variableName, ByteConsumer consumer, Periodicity periodicity);
        void registerWordConsumer(std::string variableName, WordConsumer consumer, Periodicity periodicity);
        void registerDWordConsumer(std::string variableName, DWordConsumer consumer, Periodicity periodicity);
        void registerQWordConsumer(std::string variableName, QWordConsumer consumer, Periodicity periodicity);
        void registerUnsignedByteConsumer(std::string variableName, UnsignedByteConsumer consumer, Periodicity periodicity);
        void registerUnsignedWordConsumer(std::string variableName, UnsignedWordConsumer consumer, Periodicity periodicity);
        void registerUnsignedDWordConsumer(std::string variableName, UnsignedDWordConsumer consumer, Periodicity periodicity);
        void registerUnsignedQWordConsumer(std::string variableName, UnsignedQWordConsumer consumer, Periodicity periodicity);
        void registerSingleConsumer(std::string variableName, SingleConsumer consumer, Periodicity periodicity);
        void registerDoubleConsumer(std::string variableName, DoubleConsumer consumer, Periodicity periodicity);
        void registerRawBytesConsumer(std::string variableName, RawBytesConsumer consumer, Periodicity periodicity);

        void unregisterConsumer(std::string variableName);



      private:
        std::string applicationName;
        std::string serverAddressIPv4;
        ushort serverPortTCP;

        Logger* logger;

        _internal::BufferManager* bufferManager;
        _internal::PacketPreprocessor* packetPreprocessor;

        _internal::ThreadedNetworkClient* networkClient;
        _internal::SyncQueueReader<_internal::PacketFromServer*>* dataFromServer;
        _internal::SyncQueueWriter<_internal::PacketToServer*>* dataToServer;

        _internal::EasyThread* dataReceiverThread;
        _internal::EasyThread* periodicUpdateThread;

        int iterationCounter;

        std::mutex variablesLock;

        std::map<std::string, _internal::variables::BaseVariable*> uploadVariables;
        std::map<std::string, _internal::variables::BaseVariable*> downloadVariables;

        std::map<std::string, _internal::variables::BaseVariable*> uploadVariablesToBeRegistered;
        std::map<std::string, _internal::variables::BaseVariable*> downloadVariablesToBeRegistered;


        void doPeriodicUpdate(Periodicity periodicity);
        void registerAwaitingVariablesWithServer();
        void unregisterVariablesFromServer();
        void sendUpdatedValuesToServer(std::list<_internal::variables::BaseVariable*>& vars);

        void parsePacket(void* buffer, int size);
        void parseVariablesRegistration(void* buffer, int size, int& offset);
        void parseVariablesUpdateAtServer(void* buffer, int size, int& offset);
        void parseVariablesUpdateFromServer(void* buffer, int size, int& offset);


        friend void onConnectedWithServer(void* connector);
        friend void onDisconnectedFromServer(void* connector);
        friend bool dataReceptionWorker(void* connector);
        friend bool periodicUpdateWorker(void* connector);

      }; // class DdsConnector

    } // namespace connector

  } // namespace net

} // namespace dds

#endif