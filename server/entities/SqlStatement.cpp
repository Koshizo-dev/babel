#include "SqlStatement.hpp"
#include <stdexcept>

using namespace babel;

SqliteStatement::SqliteStatement(sqlite3 *db, const std::string &sql) {
    this->_db = db;
    int rc = sqlite3_prepare_v2(this->_db, sql.c_str(), -1, &this->_stmt, nullptr);
    this->_done = false;
}

SqliteStatement::~SqliteStatement() {
    sqlite3_finalize(this->_stmt);
}

void SqliteStatement::bind(int paramIndex, const int &value) {
    int rc = sqlite3_bind_int(this->_stmt, paramIndex, value);
    if (rc != SQLITE_OK)
        throw std::runtime_error("Failed to bind int parameter: " + std::string(sqlite3_errmsg(this->_db)));
}

void SqliteStatement::bind(int paramIndex, const std::string &value) {
    int rc = sqlite3_bind_text(this->_stmt, paramIndex, value.c_str(), -1, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK)
        throw std::runtime_error("Failed to bind std::string parameter: " + std::string(sqlite3_errmsg(this->_db)));
}

void SqliteStatement::bind(int paramIndex, const uint64_t &value) {
    int rc = sqlite3_bind_int64(this->_stmt, paramIndex, value);
    if (rc != SQLITE_OK)
        throw std::runtime_error("Failed to bind uint parameter: " + std::string(sqlite3_errmsg(this->_db)));
}

bool SqliteStatement::step() {
    if (this->_done)
        return false;
    int rc = sqlite3_step(this->_stmt);
    if (rc == SQLITE_DONE) {
       this->_done = true;
       return false;
    } else if (rc == SQLITE_ROW)
        return true;
    else
        throw std::runtime_error("Failed to execute statement: " + std::string(sqlite3_errmsg(this->_db)));
}

int SqliteStatement::getInt(int colIndex) {
    return sqlite3_column_int(this->_stmt, colIndex);
}

std::int64_t SqliteStatement::getInt64(int colIndex) {
    return sqlite3_column_int64(this->_stmt, colIndex);
}

std::string SqliteStatement::getText(int colIndex) {
    const unsigned char* text = sqlite3_column_text(this->_stmt, colIndex);
    if (text != NULL)
        return std::string(reinterpret_cast<const char*>(text));
    else
        return std::string("");
}
