#include "SqlDatabase.hpp"
#include "../DatabaseError.hpp"
#include "SqlStatement.hpp"

#include <stdexcept>

using namespace babel;

SqlDatabase::SqlDatabase(std::string path): _path(path) {
}

SqlDatabase::~SqlDatabase() {
    if (this->_db)
        sqlite3_close(this->_db);
}

const void SqlDatabase::connect() {
    int rc = sqlite3_open(this->_path.c_str(), &this->_db);

    if (rc != SQLITE_OK)
        throw DatabaseError(sqlite3_errmsg(this->_db));
}

const void SqlDatabase::disconnect() const {
    sqlite3_close(this->_db);
}

const void SqlDatabase::init() const {
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
                                 "  content text not null,"
                                 "  timestamp integer not null,"
                                 "  foreign key(sender) references clients(username),"
                                 "  foreign key(receiver) references clients(username)"
                                 ");";
    this->_process(create_clients);
    this->_process(create_messages);
    this->_process(create_contacts);
}

const void SqlDatabase::addClient(std::string username) const {
    std::string insertClient = "INSERT OR IGNORE INTO clients (username) VALUES (?)";
    SqliteStatement stmt(this->_db, insertClient);
    stmt.bind(1, username);
    stmt.step();
}

const void SqlDatabase::addContact(std::string username, std::string contact) const {
    // check if sender is in recipient's contact list
    std::string selectContact = "SELECT contact FROM contacts WHERE username = ? AND contact = ?";
    SqliteStatement stmtContact(this->_db, selectContact);
    stmtContact.bind(1, username);
    stmtContact.bind(2, contact);
    bool inContacts = stmtContact.step();

    if (inContacts)
        return;

    std::string insertContact = "INSERT INTO contacts (username, contact) VALUES (?, ?)";
    SqliteStatement stmtInsertContact(this->_db, insertContact);
    stmtInsertContact.bind(1, username);
    stmtInsertContact.bind(2, contact);
    stmtInsertContact.step();
}

const void SqlDatabase::addMessage(Message &message) const {
    this->addContact(message.getSender(), message.getRecipient());
    this->addContact(message.getRecipient(), message.getSender());

    std::string insert_message = "INSERT INTO messages (sender, receiver, content, timestamp) VALUES (?, ?, ?, ?)";
    SqliteStatement stmt(this->_db, insert_message);
    stmt.bind(1, message.getSender());
    stmt.bind(2, message.getRecipient());
    stmt.bind(3, message.getContent());
    stmt.bind(4, message.getTimestamp());

    stmt.step();
}

const std::vector<Message> SqlDatabase::getMessages(std::string username) const {
    std::vector<Message> messages;

    // Query messages where username is the sender or the recipient
    std::string selectMessages = "SELECT sender, receiver, content, timestamp FROM messages WHERE sender = ? OR receiver = ?";
    SqliteStatement stmt(this->_db, selectMessages);
    stmt.bind(1, username);
    stmt.bind(2, username);

    // Iterate over the result set and construct Message objects
    while (stmt.step() == true) {
        std::string sender = stmt.getText(0);
        std::string receiver = stmt.getText(1);
        std::string content = stmt.getText(2);
        std::uint64_t timestamp = stmt.getInt64(3);
        Message message(sender, receiver, content, timestamp);
        messages.push_back(message);
    }

    return messages;
}

const std::vector<std::string> SqlDatabase::getContacts(std::string username) const {
    std::vector<std::string> contacts = {};

    std::string selectContacts = "SELECT contact FROM contacts WHERE username = ?";
    SqliteStatement stmt(this->_db, selectContacts);
    stmt.bind(1, username);

    while (stmt.step() == true) {
        std::string contact = stmt.getText(0);
        contacts.push_back(contact);
    }

    return contacts;
}

void SqlDatabase::_process(std::string request) const {
    int rc = sqlite3_exec(this->_db, request.c_str(), nullptr, nullptr, nullptr);

    if (rc != SQLITE_OK)
        throw DatabaseError(sqlite3_errmsg(this->_db));
}
