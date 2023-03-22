#pragma once

#include "../Server.hpp"

#include <asio.hpp>
#include <asio/io_service.hpp>

namespace babel {

    class AsioServer: public Server {
        public:
            AsioServer(int port);

            void run() override;
            std::vector<std::shared_ptr<Client>> getClients() override;
            void addClient(std::shared_ptr<Client> client) override;

        private:
            void _accept();

            asio::io_service _io_service;
            asio::ip::tcp::acceptor _acceptor;
            int _port;
            std::vector<std::shared_ptr<Client>> _clients = {};
    };
    
}
