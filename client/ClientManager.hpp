#pragma once

#include "Client.hpp"
#include "scenes/SceneManager.hpp"
#include "../protocol/PacketManager.hpp"
#include "EventManager.hpp"
#include "network/Transporter.hpp"

#include <mutex>
#include <vector>

namespace babel {

    class ClientManager {
        public:
            std::mutex mutex;

            std::shared_ptr<SceneManager> sceneManager = nullptr;
            std::vector<std::shared_ptr<Client>> clients = {};
            std::shared_ptr<EventManager> eventManager = nullptr;
            std::shared_ptr<PacketManager> packetManager = nullptr;
            std::shared_ptr<Client> self = nullptr;
            std::shared_ptr<Transporter> transporter = nullptr;

            std::shared_ptr<Client> getChatting();
            void reset();
            void disconnect();
    };
}