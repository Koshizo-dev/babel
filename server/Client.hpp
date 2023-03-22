#pragma once

#include "Transporter.hpp"

#include <string>
#include <memory>

namespace babel {

    class Client {
        public:
            Client(std::shared_ptr<Transporter> transporter);

            std::shared_ptr<Transporter> getTransporter();

        private:
            std::shared_ptr<Transporter> _transporter;
    };
    
}
