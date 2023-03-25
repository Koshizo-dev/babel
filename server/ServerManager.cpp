#include "ServerManager.hpp"
#include "../protocol/packets/LogoutPacket.hpp"
#include "../protocol/packets/MessagePacket.hpp"

#include <algorithm>
#include <chrono>

using namespace babel;

void ServerManager::close() {
    if (this->clients.size() == 0)
        return;
    auto current = this->clients[0];
    LogoutPacket packet;
    current->getTransporter()->sendMessage(packet.serialize());
    this->logout(current.get());
}

std::uint64_t ServerManager::getTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    return (static_cast<std::int64_t>(now_ms.time_since_epoch().count()));
}

bool ServerManager::usernameExists(const std::string &target) {
    return std::any_of(clients.begin(), clients.end(), [&](const std::shared_ptr<IoClient> &client) {
        return client->username == target;
    });
}

std::shared_ptr<IoClient> ServerManager::retrieveClient(const std::string &target) {
    for (auto client: this->clients)
        if (client->username == target)
            return (client);

    return (nullptr);
}

void ServerManager::login(IoClient *origin) {
    std::cout << "[+] " << origin->username << std::endl;
    // TODO check database, create if does not exist, otherwise send contacts to user
}

void ServerManager::logout(IoClient *origin) {
    if (origin->username == "")
        std::cout << "[-] Unknown user" << std::endl;
    else {
        origin->getTransporter()->close();
        this->clients.erase(std::remove_if(this->clients.begin(), this->clients.end(), [origin](std::shared_ptr<IoClient> client){return client.get() == origin;}), this->clients.end());
        std::cout << "[-] " << origin->username << std::endl;
    }
}

void ServerManager::sendMessage(IoClient *origin, std::string recipientName, std::string content) {
    MessagePacket message(origin->username, recipientName, content, this->getTimestamp());
    std::string serializedMessage = message.serialize();

    std::shared_ptr<IoClient> recipient = this->retrieveClient(recipientName);
    if (recipient != nullptr)
        recipient->getTransporter()->sendMessage(serializedMessage);
    origin->getTransporter()->sendMessage(serializedMessage);
    // TODO ADD ENTRY TO DATABASE
}
