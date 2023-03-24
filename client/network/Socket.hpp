#pragma once

#include "../EventManager.hpp"

#include <string>

namespace babel {

    class Socket {
        public:
            virtual bool awaitingConnection() = 0;
            virtual void closeConnection() = 0;
            virtual bool flush() = 0;
            virtual void write(std::string message) = 0;
            virtual void setEventManager(std::shared_ptr<EventManager> eventManager) = 0;
    };

}
