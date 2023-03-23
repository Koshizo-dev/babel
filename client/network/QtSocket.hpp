#pragma once

#include "Socket.hpp"
#include <QTcpSocket>

namespace babel {

    class QtSocket: public Socket {
        public:
            QtSocket(std::string hostname, unsigned int port);

            bool awaitingConnection() override;
            void closeConnection() override;
            bool flush() override;
            void write(std::string message) override;

        private:
            std::unique_ptr<QTcpSocket> _socket = nullptr;
    };
    
}
