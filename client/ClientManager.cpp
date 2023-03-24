#include "ClientManager.hpp"

using namespace babel;

std::shared_ptr<Client> ClientManager::getChatting() {
    for (std::shared_ptr<Client> client: this->clients)
        if (client->isChatting())
            return (client);
    return (nullptr);
}

void ClientManager::reset() {
    this->transporter.reset();
    this->sceneManager.reset();
    this->clients.clear();
    this->eventManager.reset();
    this->packetManager.reset();
    this->self.reset();
}

void ClientManager::disconnect() {
    this->self.reset();
    this->clients.clear();
    this->transporter.reset();
}
