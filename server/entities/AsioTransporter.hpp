#pragma once

#include "../Transporter.hpp"
#include "../IoClient.hpp"

#include <asio.hpp>
#include <asio/io_service.hpp>
#include <condition_variable>

namespace babel {

    class AsioTransporter: public Transporter {
        public:
            AsioTransporter(asio::io_service &io_service);

            void sendMessage(std::string message) override;
            void readMessage(std::function<void(std::string)> callback) override;
            void close() override;
            bool isClosed() override;

            asio::ip::tcp::socket &socket();

        private:
            void _newWrite();
            void _endWrite();
    
            asio::ip::tcp::socket _socket;
            asio::streambuf _buf;
            bool _isClosed = false;
            std::mutex _mutex;
            std::condition_variable _cv;
            std::atomic<int> _writesProcessing{0};
    };
    
}
