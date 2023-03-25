#pragma once

#include "../Database.hpp"

#include <sqlite3.h>
#include <string>
#include <memory>

namespace babel {
    class SqlDatabase: public Database {
        public:
            SqlDatabase(std::string path);
            ~SqlDatabase();

            void connect() override;
            void disconnect() override;
            void init() override;
            void addClient(std::string username) override;
            void addContact(std::string username, std::string contact) override;
            void addMessage(Message &message) override;
            std::vector<Message> getMessages(std::string username) override;
            std::vector<std::string> getContacts(std::string username) override;
            void process(std::string request);

        private:
            const std::string _path;
            sqlite3 *_db = nullptr;
    };
}
