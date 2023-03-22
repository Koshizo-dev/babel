#pragma once

#include "../Transporter.hpp"

#include <asio.hpp>
#include <asio/io_service.hpp>

namespace babel {

    class AsioTransporter: public Transporter {
        public:
            AsioTransporter(asio::io_service &io_service);

            void sendMessage(std::string) override;
            std::string readMessage() override;

            asio::ip::tcp::socket &socket();

        private:
            asio::ip::tcp::socket _socket;
            asio::streambuf _buf;
    };
    
}
