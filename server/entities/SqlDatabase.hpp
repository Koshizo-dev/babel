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
            void process(std::string request);

        private:
            const std::string _path;
            sqlite3 *_db = nullptr;
    };
}
