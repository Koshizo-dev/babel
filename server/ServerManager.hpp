#pragma once

#include "IoClient.hpp"
#include "Database.hpp"
#include "EventManager.hpp"
#include "../protocol/server/ServerPacketManager.hpp"

namespace babel {

    class ServerManager {
        public:
            std::vector<std::shared_ptr<IoClient>> clients = {};
            std::shared_ptr<Database> database = nullptr;
            std::shared_ptr<ServerPacketManager> packetManager = nullptr;
            std::shared_ptr<EventManager> eventManager = nullptr;
    };
    
}
