#include "ClientManager.hpp"
#include "Client.hpp"

using namespace babel;

const std::shared_ptr<Client> ClientManager::getClient(std::string username) const {
    for (std::shared_ptr<Client> client: this->clients)
        if (client->getUsername() == username)
            return (client);
    return (nullptr);
}

const std::shared_ptr<Client> ClientManager::getChatting() {
    for (std::shared_ptr<Client> client: this->clients)
        if (client->isChatting())
            return (client);
    return (nullptr);
}

const void ClientManager::reset() {
    this->transporter.reset();
    this->sceneManager.reset();
    this->clients.clear();
    this->eventManager.reset();
    this->packetManager.reset();
    this->self.reset();
}

const void ClientManager::disconnect() {
    this->self.reset();
    this->clients.clear();
    this->transporter.reset();
}
