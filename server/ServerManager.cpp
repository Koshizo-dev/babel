#include "ServerManager.hpp"
#include "../protocol/packets/LogoutPacket.hpp"
#include "../protocol/packets/ContactPacket.hpp"
#include "../protocol/packets/MessagePacket.hpp"
#include "../protocol/packets/CallUpPacket.hpp"
#include "../protocol/packets/HangUpPacket.hpp"

#include <algorithm>
#include <chrono>
#include <thread>

using namespace babel;

void ServerManager::close() {
    std::unique_lock<std::mutex> lock(this->_mutex);

    if (this->_clients.size() == 0)
        return;
    auto current = this->_clients[0];
    LogoutPacket packet;
    current->getTransporter()->sendMessage(packet.serialize());
    this->logout(current.get());
}

const std::uint64_t ServerManager::getTimestamp() const {
    auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    return (static_cast<std::int64_t>(now_ms.time_since_epoch().count()));
}

const void ServerManager::addClient(std::shared_ptr<IoClient> client) {
    std::unique_lock<std::mutex> lock(this->_mutex);

    this->_clients.push_back(client);
}

const bool ServerManager::usernameExists(const std::string &target) {
    std::unique_lock<std::mutex> lock(this->_mutex);

    return std::any_of(this->_clients.begin(), this->_clients.end(), [&](const std::shared_ptr<IoClient> &client) {
        return client->username == target;
    });
}

const std::shared_ptr<IoClient> ServerManager::retrieveClient(const std::string &target) {
    std::unique_lock<std::mutex> lock(this->_mutex);

    for (auto client: this->_clients)
        if (client->username == target)
            return (client);

    return (nullptr);
}

const void ServerManager::login(IoClient *origin) {
    std::cout << "[+] " << origin->username << std::endl;
    this->database->addClient(origin->username);

    std::vector<std::string> contacts = this->database->getContacts(origin->username);
    std::vector<Message> messages = this->database->getMessages(origin->username);

    for (std::string contact: contacts) {
        ContactPacket packet(contact);
        origin->getTransporter()->sendMessage(packet.serialize());
        origin->addContact(contact);
        std::shared_ptr<IoClient> foreign = this->retrieveClient(contact);
        if (foreign != nullptr && foreign->port != 0 && foreign->callTarget == origin->username) {
            CallUpPacket callUpPacket(foreign->username, foreign->getTransporter()->getHostname(), foreign->port);
            origin->getTransporter()->sendMessage(callUpPacket.serialize());
        }
    }

    for (Message message: messages) {
        MessagePacket packet(message.getSender(), message.getRecipient(), message.getContent(), message.getTimestamp());
        origin->getTransporter()->sendMessage(packet.serialize());
    }
}

const void ServerManager::logout(IoClient *origin) {
    std::unique_lock<std::mutex> lock(this->_mutex);

    if (origin->username == "") {
        std::cout << "[-] Unknown user" << std::endl;
        return;
    }
    origin->getTransporter()->close();
    this->_clients.erase(std::remove_if(this->_clients.begin(), this->_clients.end(), [origin](std::shared_ptr<IoClient> client){return client.get() == origin;}), this->_clients.end());
    std::cout << "[-] " << origin->username << std::endl;
    for (std::shared_ptr<IoClient> client: this->_clients)
        if (origin->callTarget == client->username) {
            HangUpPacket packet(origin->username);
            client->getTransporter()->sendMessage(packet.serialize());
        }
}

const void ServerManager::sendMessage(IoClient *origin, std::string recipientName, std::string content) {
    if (!origin->isContactWith(recipientName))
        origin->addContact(recipientName);
    std::shared_ptr<IoClient> recipient = this->retrieveClient(recipientName);
    std::unique_lock<std::mutex> lock(this->_mutex);
    if (recipient != nullptr) {
        if (!recipient->isContactWith(origin->username)) {
            ContactPacket packet(origin->username);
            recipient->getTransporter()->sendMessage(packet.serialize());
            recipient->addContact(origin->username);
        }
    }

    std::uint64_t timestamp = this->getTimestamp();

    MessagePacket message(origin->username, recipientName, content, timestamp);
    std::string serializedMessage = message.serialize();

    if (recipient != nullptr)
        recipient->getTransporter()->sendMessage(serializedMessage);
    origin->getTransporter()->sendMessage(serializedMessage);
    Message dbMessage(origin->username, recipientName, content, timestamp);
    this->database->addMessage(dbMessage);
}

const void ServerManager::callUp(IoClient *origin, std::string username, unsigned int port) {
    if (!origin->isContactWith(username))
        origin->addContact(username);
    std::shared_ptr<IoClient> target = this->retrieveClient(username);
    std::unique_lock<std::mutex> lock(this->_mutex);
    origin->port = port;
    origin->callTarget = username;
    if (target != nullptr) {
        if (!target->isContactWith(origin->username)) {
            ContactPacket packet(origin->username);
            target->getTransporter()->sendMessage(packet.serialize());
            target->addContact(origin->username);
        }
    }

    CallUpPacket packet(origin->username, origin->getTransporter()->getHostname(), port);
    std::string serialized = packet.serialize();

    if (target != nullptr)
        target->getTransporter()->sendMessage(packet.serialize());
    origin->getTransporter()->sendMessage(serialized);
}

const void ServerManager::hangUp(IoClient *origin, std::string username) {
    std::shared_ptr<IoClient> target = this->retrieveClient(username);
    std::unique_lock<std::mutex> lock(this->_mutex);
    origin->port = 0;
    origin->callTarget = "";

    HangUpPacket packet(origin->username);
    std::string serialized = packet.serialize();

    if (target != nullptr)
        target->getTransporter()->sendMessage(packet.serialize());
    origin->getTransporter()->sendMessage(serialized);
}
