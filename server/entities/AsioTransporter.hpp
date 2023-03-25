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

            const void sendMessage(std::string message) override;
            const void readMessage(std::function<void(std::string)> callback) override;
            const void close() override;
            const bool isClosed() const override;

            asio::ip::tcp::socket &socket();

        private:
            const void _newWrite();
            const void _endWrite();
    
            asio::ip::tcp::socket _socket;
            asio::streambuf _buf;
            bool _isClosed = false;
            std::mutex _mutex;
            std::condition_variable _cv;
            std::atomic<int> _writesProcessing{0};
    };
    
}
