#pragma once

#include "../Server.hpp"
#include "../ServerManager.hpp"

#include <asio.hpp>
#include <asio/io_service.hpp>

namespace babel {

    class AsioServer: public Server {
        public:
            AsioServer(int port, std::shared_ptr<ServerManager> serverManager);

            void run() override;

        private:
            void _accept();

            asio::io_service _io_service;
            asio::ip::tcp::acceptor _acceptor;
            int _port;
            std::shared_ptr<ServerManager> _serverManager;
    };
    
}
