#pragma once

#include "Message.hpp"

#include <string>
#include <vector>

namespace babel {
    class Database {
        public:
            virtual void connect() = 0;
            virtual void disconnect() const = 0;
            virtual void init() const = 0;
            virtual void addClient(std::string username) const = 0;
            virtual void addContact(std::string username, std::string contact) const = 0;
            virtual void addMessage(Message &message) const = 0;
            virtual std::vector<Message> getMessages(std::string username) const = 0;
            virtual std::vector<std::string> getContacts(std::string username) const = 0;
    };
}
