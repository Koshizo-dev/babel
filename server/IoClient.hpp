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

            const void addContact(std::string username);
            const bool isContactWith(std::string username) const;
            const std::shared_ptr<Transporter> getTransporter() const;

            std::string username = "";
            unsigned int port = 0;
            std::string callTarget = "";

        private:
            const void _handle();

            std::shared_ptr<EventManager> _eventManager;
            std::vector<std::string> _contacts = {};
            std::shared_ptr<Transporter> _transporter;
    };

}
