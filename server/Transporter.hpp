#pragma once

#include <string>

namespace babel {

    class Transporter {
        public:
            virtual void sendMessage(std::string message) = 0;
            virtual std::string readMessage() = 0;
    };

}
