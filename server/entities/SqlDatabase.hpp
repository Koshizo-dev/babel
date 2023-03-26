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

            const void connect() override;
            const void disconnect() const override;
            const void init() const override;
            const void addClient(std::string username) const override;
            const void addContact(std::string username, std::string contact) const override;
            const void addMessage(Message &message) const override;
            const std::vector<Message> getMessages(std::string username) const override;
            const std::vector<std::string> getContacts(std::string username) const override;

        private:
            void _process(std::string request) const;

            const std::string _path;
            sqlite3 *_db = nullptr;
    };
}
