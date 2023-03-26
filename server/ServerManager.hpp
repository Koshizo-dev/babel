#pragma once

#include "IoClient.hpp"
#include "Database.hpp"
#include "EventManager.hpp"
#include "../protocol/server/ServerPacketManager.hpp"

#include <mutex>

namespace babel {

    class ServerManager {
        public:
            void close();
            const std::uint64_t getTimestamp() const;

            const void addClient(std::shared_ptr<IoClient> client);
            const bool usernameExists(const std::string &target);
            const std::shared_ptr<IoClient> retrieveClient(const std::string &target);
            const void login(IoClient *origin);
            const void logout(IoClient *origin);
            const void sendMessage(IoClient *origin, std::string recipientName, std::string content);
            const void callUp(IoClient *origin, std::string username, unsigned int port);
            const void hangUp(IoClient *origin, std::string username);

            std::shared_ptr<Database> database = nullptr;
            std::shared_ptr<ServerPacketManager> packetManager = nullptr;
            std::shared_ptr<EventManager> eventManager = nullptr;

        private:
            std::vector<std::shared_ptr<IoClient>> _clients = {};

            std::mutex _mutex;
    };

}
