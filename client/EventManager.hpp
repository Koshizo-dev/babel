#pragma once

#include "../protocol/client/ClientPacketManager.hpp"

#include <string>

namespace babel {

    class ClientManager;

    class EventManager {
        public:
            EventManager(std::shared_ptr<ClientManager> clientManager, std::shared_ptr<PacketManager> _packetManager);

            void handlePacket(std::string message);

        private:
            const std::shared_ptr<PacketManager> _packetManager;
            const std::shared_ptr<ClientManager> _clientManager;
    };
    
}
