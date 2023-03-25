#include "ServerManager.hpp"
#include "../protocol/packets/LogoutPacket.hpp"

#include <algorithm>

using namespace babel;

void ServerManager::close() {
    if (this->clients.size() == 0)
        return;
    auto current = this->clients[0];
    LogoutPacket packet;
    current->getTransporter()->sendMessage(packet.serialize());
    this->logout(current.get());
}

bool ServerManager::usernameExists(const std::string &target) {
    return std::any_of(clients.begin(), clients.end(), [&](const std::shared_ptr<IoClient> &client) {
        return client->username == target;
    });
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
