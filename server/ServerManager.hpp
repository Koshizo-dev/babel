#pragma once

#include "IoClient.hpp"
#include "Database.hpp"
#include "EventManager.hpp"
#include "../protocol/server/ServerPacketManager.hpp"

namespace babel {

    class ServerManager {
        public:
            void close();
            std::uint64_t getTimestamp();

            bool usernameExists(const std::string &target);
            std::shared_ptr<IoClient> retrieveClient(const std::string &target);
            void login(IoClient *origin);
            void logout(IoClient *origin);
            void sendMessage(IoClient *origin, std::string recipientName, std::string content);

            std::vector<std::shared_ptr<IoClient>> clients = {};
            std::shared_ptr<Database> database = nullptr;
            std::shared_ptr<ServerPacketManager> packetManager = nullptr;
            std::shared_ptr<EventManager> eventManager = nullptr;
    };

}
