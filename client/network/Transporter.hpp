#pragma once

#include "Socket.hpp"
#include <memory>

namespace babel {

    class Transporter {
        public:
            Transporter(std::unique_ptr<Socket> socket);

            bool awaitingConnection();
            void closeConnection();
            void sendMessage(std::string message);
            std::string readMessage();

        private:
            const std::unique_ptr<Socket> _socket;
    };
    
}
