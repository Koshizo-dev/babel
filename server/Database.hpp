#pragma once

#include "Message.hpp"

#include <string>
#include <vector>

namespace babel {
    class Database {
        public:
            virtual void connect() = 0;
            virtual void disconnect() = 0;
            virtual void init() = 0;
            virtual void addClient(std::string username) = 0;
            virtual void addContact(std::string username, std::string contact) = 0;
            virtual void addMessage(Message &message) = 0;
            virtual std::vector<Message> getMessages(std::string username) = 0;
            virtual std::vector<std::string> getContacts(std::string username) = 0;
    };
}
