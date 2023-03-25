#include "SqlDatabase.hpp"
#include "../DatabaseError.hpp"

using namespace babel;

SqlDatabase::SqlDatabase(std::string path): _path(path) {
}

SqlDatabase::~SqlDatabase() {
    if (this->_db)
        sqlite3_close(this->_db);
}

void SqlDatabase::connect() {
    int rc = sqlite3_open(this->_path.c_str(), &this->_db);

    if (rc != SQLITE_OK)
        throw DatabaseError(sqlite3_errmsg(this->_db));
}

void SqlDatabase::disconnect() {
    sqlite3_close(this->_db);
}

void SqlDatabase::init() {
    std::string create_clients = "CREATE TABLE IF NOT EXISTS clients ("
                                 "  username text primary key not null"
                                 ");";
    std::string create_contacts = "CREATE TABLE IF NOT EXISTS contacts ("
                                 "  username text not null,"
                                 "  contact text not null,"
                                 "  foreign key(username) references clients(username),"
                                 "  primary key(username, contact)"
                                 ");";
    
    std::string create_messages = "CREATE TABLE IF NOT EXISTS messages ("
                                 "  sender text not null,"
                                 "  receiver text not null,"
                                 "  message text not null,"
                                 "  foreign key(sender) references clients(username),"
                                 "  foreign key(receiver) references clients(username)"
                                 ");";
    this->process(create_clients);
    this->process(create_messages);
    this->process(create_contacts);
}

void SqlDatabase::addClient(std::string username) {
}

void SqlDatabase::addContact(std::string username, std::string contact) {
}

void SqlDatabase::addMessage(Message &message) {
}

std::vector<Message> SqlDatabase::getMessages(std::string username) {
    return {};
}

std::vector<std::string> SqlDatabase::getContacts(std::string usernam) {
    return {};
}

void SqlDatabase::process(std::string request) {
    int rc = sqlite3_exec(this->_db, request.c_str(), nullptr, nullptr, nullptr);

    if (rc != SQLITE_OK)
        throw DatabaseError(sqlite3_errmsg(this->_db));
}
