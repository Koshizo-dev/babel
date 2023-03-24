#pragma once

#include "Socket.hpp"
#include "../EventManager.hpp"

#include <memory>

namespace babel {

    class Transporter {
        public:
            Transporter(std::shared_ptr<EventManager>, std::unique_ptr<Socket> socket);
            ~Transporter();

            bool awaitingConnection();
            void closeConnection();
            void sendMessage(std::string message);
            std::string readMessage();

        private:
            const std::unique_ptr<Socket> _socket;
            const std::shared_ptr<EventManager> _eventManager;
    };
    
}
