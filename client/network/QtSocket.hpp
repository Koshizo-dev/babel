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
            void setEventManager(std::shared_ptr<EventManager> eventManager) override;

        private:
            std::shared_ptr<EventManager> _eventManager = nullptr;
            std::unique_ptr<QTcpSocket> _socket = nullptr;
            void (EventManager::* _readHandler)(std::string message) = nullptr;
    };
    
}
