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
        


      public:

        //- 
        //- Providers
        //- 

        public void RegisterStringProvider(string variableName, StringProvider provider, Periodicity periodicity)
        {
          lock(variablesMutex)
          {
            if (uploadVariables.ContainsKey(variableName) ||
              uploadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision to the server.");
            }
            else
            {
              uploadVariablesToBeRegistered.Add(variableName, new StringVariable(variableName, periodicity, provider));
            }
          }
        }
        /// <summary>
        /// Registers a provider delegate for providing "Boolean" to the server at given periodicity.
        /// </summary>
        /// <param name="variableName">Variable's name.</param>
        /// <param name="provider">The delegate.</param>
        /// <param name="periodicity">Periodicity.</param>
        public void RegisterBooleanProvider(string variableName, BooleanProvider provider, Periodicity periodicity)
        {
          lock(variablesMutex)
          {
            if (uploadVariables.ContainsKey(variableName) ||
              uploadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision to the server.");
            }
            else
            {
              uploadVariablesToBeRegistered.Add(variableName, new BooleanVariable(variableName, periodicity, provider));
            }
          }
        }
        /// <summary>
        /// Registers a provider delegate for providing "Signed Byte" to the server at given periodicity.
        /// </summary>
        /// <param name="variableName">Variable's name.</param>
        /// <param name="provider">The delegate.</param>
        /// <param name="periodicity">Periodicity.</param>
        public void RegisterByteProvider(string variableName, ByteProvider provider, Periodicity periodicity)
        {
          lock(variablesMutex)
          {
            if (uploadVariables.ContainsKey(variableName) ||
              uploadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision to the server.");
            }
            else
            {
              uploadVariablesToBeRegistered.Add(variableName, new ByteVariable(variableName, periodicity, provider));
            }
          }
        }
        /// <summary>
        /// Registers a provider delegate for providing "Signed Word" to the server at given periodicity.
        /// </summary>
        /// <param name="variableName">Variable's name.</param>
        /// <param name="provider">The delegate.</param>
        /// <param name="periodicity">Periodicity.</param>
        public void RegisterWordProvider(string variableName, WordProvider provider, Periodicity periodicity)
        {
          lock(variablesMutex)
          {
            if (uploadVariables.ContainsKey(variableName) ||
              uploadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision to the server.");
            }
            else
            {
              uploadVariablesToBeRegistered.Add(variableName, new WordVariable(variableName, periodicity, provider));
            }
          }
        }
        /// <summary>
        /// Registers a provider delegate for providing "Signed Double Word" to the server at given periodicity.
        /// </summary>
        /// <param name="variableName">Variable's name.</param>
        /// <param name="provider">The delegate.</param>
        /// <param name="periodicity">Periodicity.</param>
        public void RegisterDWordProvider(string variableName, DWordProvider provider, Periodicity periodicity)
        {
          lock(variablesMutex)
          {
            if (uploadVariables.ContainsKey(variableName) ||
              uploadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision to the server.");
            }
            else
            {
              uploadVariablesToBeRegistered.Add(variableName, new DWordVariable(variableName, periodicity, provider));
            }
          }
        }
        /// <summary>
        /// Registers a provider delegate for providing "Signed Quad Word" to the server at given periodicity.
        /// </summary>
        /// <param name="variableName">Variable's name.</param>
        /// <param name="provider">The delegate.</param>
        /// <param name="periodicity">Periodicity.</param>
        public void RegisterQWordProvider(string variableName, QWordProvider provider, Periodicity periodicity)
        {
          lock(variablesMutex)
          {
            if (uploadVariables.ContainsKey(variableName) ||
              uploadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision to the server.");
            }
            else
            {
              uploadVariablesToBeRegistered.Add(variableName, new QWordVariable(variableName, periodicity, provider));
            }
          }
        }
        /// <summary>
        /// Registers a provider delegate for providing "Unsigned Byte" to the server at given periodicity.
        /// </summary>
        /// <param name="variableName">Variable's name.</param>
        /// <param name="provider">The delegate.</param>
        /// <param name="periodicity">Periodicity.</param>
        public void RegisterUnsignedByteProvider(string variableName, UnsignedByteProvider provider, Periodicity periodicity)
        {
          lock(variablesMutex)
          {
            if (uploadVariables.ContainsKey(variableName) ||
              uploadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision to the server.");
            }
            else
            {
              uploadVariablesToBeRegistered.Add(variableName, new UnsignedByteVariable(variableName, periodicity, provider));
            }
          }
        }
        /// <summary>
        /// Registers a provider delegate for providing "Unsigned Word" to the server at given periodicity.
        /// </summary>
        /// <param name="variableName">Variable's name.</param>
        /// <param name="provider">The delegate.</param>
        /// <param name="periodicity">Periodicity.</param>
        public void RegisterUnsignedWordProvider(string variableName, UnsignedWordProvider provider, Periodicity periodicity)
        {
          lock(variablesMutex)
          {
            if (uploadVariables.ContainsKey(variableName) ||
              uploadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision to the server.");
            }
            else
            {
              uploadVariablesToBeRegistered.Add(variableName, new UnsignedWordVariable(variableName, periodicity, provider));
            }
          }
        }
        /// <summary>
        /// Registers a provider delegate for providing "Unsigned Double Word" to the server at given periodicity.
        /// </summary>
        /// <param name="variableName">Variable's name.</param>
        /// <param name="provider">The delegate.</param>
        /// <param name="periodicity">Periodicity.</param>
        public void RegisterUnsignedDWordProvider(string variableName, UnsignedDWordProvider provider, Periodicity periodicity)
        {
          lock(variablesMutex)
          {
            if (uploadVariables.ContainsKey(variableName) ||
              uploadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision to the server.");
            }
            else
            {
              uploadVariablesToBeRegistered.Add(variableName, new UnsignedDWordVariable(variableName, periodicity, provider));
            }
          }
        }
        /// <summary>
        /// Registers a provider delegate for providing "Unsigned Quad Word" to the server at given periodicity.
        /// </summary>
        /// <param name="variableName">Variable's name.</param>
        /// <param name="provider">The delegate.</param>
        /// <param name="periodicity">Periodicity.</param>
        public void RegisterUnsignedQWordProvider(string variableName, UnsignedQWordProvider provider, Periodicity periodicity)
        {
          lock(variablesMutex)
          {
            if (uploadVariables.ContainsKey(variableName) ||
              uploadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision to the server.");
            }
            else
            {
              uploadVariablesToBeRegistered.Add(variableName, new UnsignedQWordVariable(variableName, periodicity, provider));
            }
          }
        }
        /// <summary>
        /// Registers a provider delegate for providing "Single - 4 byte floating-point" to the server at given periodicity.
        /// </summary>
        /// <param name="variableName">Variable's name.</param>
        /// <param name="provider">The delegate.</param>
        /// <param name="periodicity">Periodicity.</param>
        public void RegisterSingleProvider(string variableName, SingleProvider provider, Periodicity periodicity)
        {
          lock(variablesMutex)
          {
            if (uploadVariables.ContainsKey(variableName) ||
              uploadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision to the server.");
            }
            else
            {
              uploadVariablesToBeRegistered.Add(variableName, new SingleVariable(variableName, periodicity, provider));
            }
          }
        }
        /// <summary>
        /// Registers a provider delegate for providing "Double - 8 byte floating-point" to the server at given periodicity.
        /// </summary>
        /// <param name="variableName">Variable's name.</param>
        /// <param name="provider">The delegate.</param>
        /// <param name="periodicity">Periodicity.</param>
        public void RegisterDoubleProvider(string variableName, DoubleProvider provider, Periodicity periodicity)
        {
          lock(variablesMutex)
          {
            if (uploadVariables.ContainsKey(variableName) ||
              uploadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision to the server.");
            }
            else
            {
              uploadVariablesToBeRegistered.Add(variableName, new DoubleVariable(variableName, periodicity, provider));
            }
          }
        }
        /// <summary>
        /// Registers a provider delegate for providing "bytes array" to the server at given periodicity.
        /// </summary>
        /// <param name="variableName">Variable's name.</param>
        /// <param name="provider">The delegate.</param>
        /// <param name="periodicity">Periodicity.</param>
        public void RegisterRawBytesProvider(string variableName, RawBytesProvider provider, Periodicity periodicity)
        {
          lock(variablesMutex)
          {
            if (uploadVariables.ContainsKey(variableName) ||
              uploadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision to the server.");
            }
            else
            {
              uploadVariablesToBeRegistered.Add(variableName, new RawBytesVariable(variableName, periodicity, provider));
            }
          }
        }

        /// <summary>
        /// Unregisters providing named variable to the server.
        /// </summary>
        /// <param name="variableName">Variable's name.</param>
        public void UnregisterProvider(string variableName)
        {
          lock(variablesMutex)
          {
            if (uploadVariables.ContainsKey(variableName))
            {
              uploadVariables.Remove(variableName);
            }

            if (uploadVariablesToBeRegistered.ContainsKey(variableName))
            {
              uploadVariablesToBeRegistered.Remove(variableName);
            }
          }
        }
        #endregion
          #region Consumers
          //- 
          //- Consumers
          //- 

          /// <summary>
          /// Registers a consumer delegate for receiving "String" from the server at given periodicity.
          /// </summary>
          /// <param name="variableName">Variable's name.</param>
          /// <param name="provider">The delegate.</param>
          /// <param name="periodicity">Periodicity.</param>
          public void RegisterStringConsumer(string variableName, StringConsumer consumer, Periodicity periodicity)
        {
          lock(variablesMutex)
          {
            if (downloadVariables.ContainsKey(variableName) ||
              downloadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision from the server.");
            }
            else
            {
              downloadVariablesToBeRegistered.Add(
                variableName, new StringVariable(variableName, periodicity, null!, consumer));
            }
          }
        }
        /// <summary>
        /// Registers a consumer delegate for receiving "Boolean" from the server at given periodicity.
        /// </summary>
        /// <param name="variableName">Variable's name.</param>
        /// <param name="provider">The delegate.</param>
        /// <param name="periodicity">Periodicity.</param>
        public void RegisterBooleanConsumer(string variableName, BooleanConsumer consumer, Periodicity periodicity)
        {
          lock(variablesMutex)
          {
            if (downloadVariables.ContainsKey(variableName) ||
              downloadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision from the server.");
            }
            else
            {
              downloadVariablesToBeRegistered.Add(
                variableName, new BooleanVariable(variableName, periodicity, null!, consumer));
            }
          }
        }
        /// <summary>
        /// Registers a consumer delegate for receiving "Signed Byte" from the server at given periodicity.
        /// </summary>
        /// <param name="variableName">Variable's name.</param>
        /// <param name="provider">The delegate.</param>
        /// <param name="periodicity">Periodicity.</param>
        public void RegisterByteConsumer(string variableName, ByteConsumer consumer, Periodicity periodicity)
        {
          lock(variablesMutex)
          {
            if (downloadVariables.ContainsKey(variableName) ||
              downloadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision from the server.");
            }
            else
            {
              downloadVariablesToBeRegistered.Add(
                variableName, new ByteVariable(variableName, periodicity, null!, consumer));
            }
          }
        }
        /// <summary>
        /// Registers a consumer delegate for receiving "Signed Word" from the server at given periodicity.
        /// </summary>
        /// <param name="variableName">Variable's name.</param>
        /// <param name="provider">The delegate.</param>
        /// <param name="periodicity">Periodicity.</param>
        public void RegisterWordConsumer(string variableName, WordConsumer consumer, Periodicity periodicity)
        {
          lock(variablesMutex)
          {
            if (downloadVariables.ContainsKey(variableName) ||
              downloadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision from the server.");
            }
            else
            {
              downloadVariablesToBeRegistered.Add(
                variableName, new WordVariable(variableName, periodicity, null!, consumer));
            }
          }
        }
        /// <summary>
        /// Registers a consumer delegate for receiving "Signed Double Word" from the server at given periodicity.
        /// </summary>
        /// <param name="variableName">Variable's name.</param>
        /// <param name="provider">The delegate.</param>
        /// <param name="periodicity">Periodicity.</param>
        public void RegisterDWordConsumer(string variableName, DWordConsumer consumer, Periodicity periodicity)
        {
          lock(variablesMutex)
          {
            if (downloadVariables.ContainsKey(variableName) ||
              downloadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision from the server.");
            }
            else
            {
              downloadVariablesToBeRegistered.Add(
                variableName, new DWordVariable(variableName, periodicity, null!, consumer));
            }
          }
        }
        /// <summary>
        /// Registers a consumer delegate for receiving "Signed Quad Word" from the server at given periodicity.
        /// </summary>
        /// <param name="variableName">Variable's name.</param>
        /// <param name="provider">The delegate.</param>
        /// <param name="periodicity">Periodicity.</param>
        public void RegisterQWordConsumer(string variableName, QWordConsumer consumer, Periodicity periodicity)
        {
          lock(variablesMutex)
          {
            if (downloadVariables.ContainsKey(variableName) ||
              downloadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision from the server.");
            }
            else
            {
              downloadVariablesToBeRegistered.Add(
                variableName, new QWordVariable(variableName, periodicity, null!, consumer));
            }
          }
        }
        /// <summary>
        /// Registers a consumer delegate for receiving "Unsigned Byte" from the server at given periodicity.
        /// </summary>
        /// <param name="variableName">Variable's name.</param>
        /// <param name="provider">The delegate.</param>
        /// <param name="periodicity">Periodicity.</param>
        public void RegisterUnsignedByteConsumer(string variableName, UnsignedByteConsumer consumer, Periodicity periodicity)
        {
          lock(variablesMutex)
          {
            if (downloadVariables.ContainsKey(variableName) ||
              downloadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision from the server.");
            }
            else
            {
              downloadVariablesToBeRegistered.Add(
                variableName, new UnsignedByteVariable(variableName, periodicity, null!, consumer));
            }
          }
        }
        /// <summary>
        /// Registers a consumer delegate for receiving "Unsigned Word" from the server at given periodicity.
        /// </summary>
        /// <param name="variableName">Variable's name.</param>
        /// <param name="provider">The delegate.</param>
        /// <param name="periodicity">Periodicity.</param>
        public void RegisterUnsignedWordConsumer(string variableName, UnsignedWordConsumer consumer, Periodicity periodicity)
        {
          lock(variablesMutex)
          {
            if (downloadVariables.ContainsKey(variableName) ||
              downloadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision from the server.");
            }
            else
            {
              downloadVariablesToBeRegistered.Add(
                variableName, new UnsignedWordVariable(variableName, periodicity, null!, consumer));
            }
          }
        }
        /// <summary>
        /// Registers a consumer delegate for receiving "Unsigned Double Word" from the server at given periodicity.
        /// </summary>
        /// <param name="variableName">Variable's name.</param>
        /// <param name="provider">The delegate.</param>
        /// <param name="periodicity">Periodicity.</param>
        public void RegisterUnsignedDWordConsumer(string variableName, UnsignedDWordConsumer consumer, Periodicity periodicity)
        {
          lock(variablesMutex)
          {
            if (downloadVariables.ContainsKey(variableName) ||
              downloadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision from the server.");
            }
            else
            {
              downloadVariablesToBeRegistered.Add(
                variableName, new UnsignedDWordVariable(variableName, periodicity, null!, consumer));
            }
          }
        }
        /// <summary>
        /// Registers a consumer delegate for receiving "Unsigned Quad Word" from the server at given periodicity.
        /// </summary>
        /// <param name="variableName">Variable's name.</param>
        /// <param name="provider">The delegate.</param>
        /// <param name="periodicity">Periodicity.</param>
        public void RegisterUnsignedQWordConsumer(string variableName, UnsignedQWordConsumer consumer, Periodicity periodicity)
        {
          lock(variablesMutex)
          {
            if (downloadVariables.ContainsKey(variableName) ||
              downloadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision from the server.");
            }
            else
            {
              downloadVariablesToBeRegistered.Add(
                variableName, new UnsignedQWordVariable(variableName, periodicity, null!, consumer));
            }
          }
        }
        /// <summary>
        /// Registers a consumer delegate for receiving "Single - 4 byte floating-point number"
        /// from the server at given periodicity.
        /// </summary>
        /// <param name="variableName">Variable's name.</param>
        /// <param name="provider">The delegate.</param>
        /// <param name="periodicity">Periodicity.</param>
        public void RegisterSingleConsumer(string variableName, SingleConsumer consumer, Periodicity periodicity)
        {
          lock(variablesMutex)
          {
            if (downloadVariables.ContainsKey(variableName) ||
              downloadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision from the server.");
            }
            else
            {
              downloadVariablesToBeRegistered.Add(
                variableName, new SingleVariable(variableName, periodicity, null!, consumer));
            }
          }
        }
        /// <summary>
        /// Registers a consumer delegate for receiving "Double - 8 byte floating-point number"
        /// from the server at given periodicity.
        /// </summary>
        /// <param name="variableName">Variable's name.</param>
        /// <param name="provider">The delegate.</param>
        /// <param name="periodicity">Periodicity.</param>
        public void RegisterDoubleConsumer(string variableName, DoubleConsumer consumer, Periodicity periodicity)
        {
          lock(variablesMutex)
          {
            if (downloadVariables.ContainsKey(variableName) ||
              downloadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision from the server.");
            }
            else
            {
              downloadVariablesToBeRegistered.Add(
                variableName, new DoubleVariable(variableName, periodicity, null!, consumer));
            }
          }
        }
        /// <summary>
        /// Registers a consumer delegate for receiving "bytes array" from the server at given periodicity.
        /// </summary>
        /// <param name="variableName">Variable's name.</param>
        /// <param name="provider">The delegate.</param>
        /// <param name="periodicity">Periodicity.</param>
        public void RegisterRawBytesConsumer(string variableName, RawBytesConsumer consumer, Periodicity periodicity)
        {
          lock(variablesMutex)
          {
            if (downloadVariables.ContainsKey(variableName) ||
              downloadVariablesToBeRegistered.ContainsKey(variableName))
            {
              throw new Exception(
                $"The variable named {variableName} " +
                $"has already been registered for provision from the server.");
            }
            else
            {
              downloadVariablesToBeRegistered.Add(
                variableName, new RawBytesVariable(variableName, periodicity, null!, consumer));
            }
          }
        }

        /// <summary>
        /// Unregisters getting named variable from the server.
        /// </summary>
        /// <param name="variableName">Variable's name.</param>
        public void UnregisterConsumer(string variableName)
        {
          lock(variablesMutex)
          {
            if (downloadVariables.ContainsKey(variableName))
            {
              downloadVariables.Remove(variableName);
            }

            if (downloadVariablesToBeRegistered.ContainsKey(variableName))
            {
              downloadVariablesToBeRegistered.Remove(variableName);
            }
          }
        }
      };

    }
  }
}

#endif