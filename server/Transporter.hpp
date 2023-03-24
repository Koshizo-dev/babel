#pragma once

#include <functional>
#include <string>
#include <memory>

namespace babel {

    class Transporter {
        public:
            virtual void sendMessage(std::string message) = 0;
            virtual void readMessage(std::function<void(std::string)> callback) = 0;
    };

}
