#include "AsioServer.hpp"
#include "AsioTransporter.hpp"

#include <iostream>

using namespace babel;

AsioServer::AsioServer(int port, std::shared_ptr<ServerManager> serverManager): _acceptor(_io_service, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)) {
    this->_port = port;
    this->_serverManager = serverManager;
    this->_accept();
}

void AsioServer::run() {
    std::cout << "Server up! Port=" << this->_port << std::endl;
    this->_io_service.run();
}

void AsioServer::_accept() {
    auto new_transporter = std::make_shared<AsioTransporter>(this->_io_service);

    this->_acceptor.async_accept(new_transporter->socket(),
        [this, new_transporter](std::error_code ec) {
            if (!ec) {
                this->_serverManager->clients.push_back(std::make_shared<IoClient>(this->_serverManager->eventManager, new_transporter));
            }
            this->_accept();
        });
}
