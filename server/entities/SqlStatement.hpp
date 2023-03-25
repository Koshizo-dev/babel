#pragma once

#include <sqlite3.h>
#include <string>

namespace babel {

class SqliteStatement {
public:
    SqliteStatement(sqlite3 *db, const std::string &sql);

    ~SqliteStatement();

    void bind(int paramIndex, const int &value);

    void bind(int paramIndex, const uint64_t &value);

    void bind(int paramIndex, const std::string &value);

    bool step();

    int getInt(int colIndex);
    
    std::int64_t getInt64(int colIndex);

    std::string getText(int colIndex);

    private:
        sqlite3 *_db;
        sqlite3_stmt *_stmt;
        bool _done;
    };
}