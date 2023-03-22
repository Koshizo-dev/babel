#include "AsioServer.hpp"
#include "AsioTransporter.hpp"

#include <iostream>

using namespace babel;

AsioServer::AsioServer(int port): _acceptor(_io_service, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)) {
    this->_port = port;
    this->_accept();
}

void AsioServer::run() {
    this->_io_service.run();
    std::cout << "Server up! Port=" << this->_port << std::endl;
}

std::vector<std::shared_ptr<Client>> AsioServer::getClients() {
    return (this->_clients);
}

void AsioServer::addClient(std::shared_ptr<Client> client) {
    this->_clients.push_back(client);
}

void AsioServer::_accept() {
    auto new_transporter = std::make_shared<AsioTransporter>(this->_io_service);

    this->_acceptor.async_accept(new_transporter->socket(),
        [this, new_transporter](std::error_code ec) {
            if (!ec) {
                this->addClient(std::shared_ptr<Client>(new Client(new_transporter)));
            }
            this->_accept();
        });
}
