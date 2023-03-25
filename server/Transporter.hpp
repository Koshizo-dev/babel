#pragma once

#include <functional>
#include <string>
#include <memory>

namespace babel {

    class Transporter {
        public:
            virtual const void sendMessage(std::string message) = 0;
            virtual const void readMessage(std::function<void(std::string)> callback) = 0;
            virtual const void close() = 0;
            virtual const bool isClosed() const = 0;
    };

}
