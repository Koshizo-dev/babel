#pragma once

#include "../protocol/client/ClientPacketManager.hpp"

#include <string>

namespace babel {

    class EventManager {
        public:
            EventManager(std::shared_ptr<PacketManager> _packetManager);

            void handlePacket(std::string message);

        private:
            const std::shared_ptr<PacketManager> _packetManager;
    };
    
}
