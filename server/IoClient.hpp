#pragma once

#include "Transporter.hpp"

#include <string>
#include <memory>
#include <vector>

namespace babel {

    class EventManager;

    class IoClient {
        public:
            IoClient(std::shared_ptr<EventManager>, std::shared_ptr<Transporter> transporter);

            void addContact(std::string username);
            bool isContactWith(std::string username);
            std::string username = "";
            std::shared_ptr<Transporter> getTransporter();

        private:
            void _handle();
            std::shared_ptr<EventManager> _eventManager;
            std::vector<std::string> _contacts = {};
            std::shared_ptr<Transporter> _transporter;
    };

}
