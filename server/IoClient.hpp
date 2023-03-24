#pragma once

#include "Transporter.hpp"

#include <string>
#include <memory>

namespace babel {

    class EventManager;

    class IoClient {
        public:
            IoClient(std::shared_ptr<EventManager>, std::shared_ptr<Transporter> transporter);

            std::shared_ptr<Transporter> getTransporter();

        private:
            void _handle();
    
            std::shared_ptr<EventManager> _eventManager;
            std::shared_ptr<Transporter> _transporter;
    };
    
}
