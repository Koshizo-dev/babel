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
            void disconnect() const override;
            void init() const override;
            void addClient(std::string username) const override;
            void addContact(std::string username, std::string contact) const override;
            void addMessage(Message &message) const override;
            std::vector<Message> getMessages(std::string username) const override;
            std::vector<std::string> getContacts(std::string username) const override;

        private:
            void _process(std::string request) const;

            const std::string _path;
            sqlite3 *_db = nullptr;
    };
}
