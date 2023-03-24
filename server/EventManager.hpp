#pragma once

#include "../protocol/server/ServerPacketManager.hpp"
#include "IoClient.hpp"

namespace babel {

    class EventManager {
        public:
            EventManager(std::shared_ptr<ServerPacketManager> packetManager);

            void handlePacket(IoClient *origin, std::string serialized);

        private:
            std::shared_ptr<ServerPacketManager> _packetManager;
    };
    
}
