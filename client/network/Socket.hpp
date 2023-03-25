#pragma once

#include "../EventManager.hpp"

#include <string>

namespace babel {

    class Socket {
        public:
            virtual const bool awaitingConnection() = 0;
            virtual const void closeConnection() = 0;
            virtual const bool flush() = 0;
            virtual const void write(std::string message) = 0;
            virtual const void setEventManager(std::shared_ptr<EventManager> eventManager) = 0;
    };

}
