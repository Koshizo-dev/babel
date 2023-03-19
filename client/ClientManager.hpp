#pragma once

#include "scenes/SceneManager.hpp"

namespace babel {

    class ClientManager {
        public:
            std::shared_ptr<SceneManager> sceneManager = nullptr;
    
    };
}