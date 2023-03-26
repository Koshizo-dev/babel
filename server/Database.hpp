#pragma once

#include "Message.hpp"

#include <string>
#include <vector>

namespace babel {
    class Database {
        public:
            virtual const void connect() = 0;
            virtual const void disconnect() const = 0;
            virtual const void init() const = 0;
            virtual const void addClient(std::string username) const = 0;
            virtual const void addContact(std::string username, std::string contact) const = 0;
            virtual const void addMessage(Message &message) const = 0;
            virtual const std::vector<Message> getMessages(std::string username) const = 0;
            virtual const std::vector<std::string> getContacts(std::string username) const = 0;
    };
}
