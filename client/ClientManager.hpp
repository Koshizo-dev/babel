#pragma once

#include "Client.hpp"
#include "scenes/SceneManager.hpp"
#include <vector>

namespace babel {
    class ClientManager {
        public:
            std::shared_ptr<SceneManager> sceneManager = nullptr;
            std::vector<std::shared_ptr<Client>> clients = {};
            std::shared_ptr<Client> self = nullptr;

            std::shared_ptr<Client> getChatting();
    };
}