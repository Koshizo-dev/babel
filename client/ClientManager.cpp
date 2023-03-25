#include "ClientManager.hpp"
#include "Client.hpp"

using namespace babel;

std::shared_ptr<Client> ClientManager::getClient(std::string username) {
    std::unique_lock<std::mutex> lock(this->mutex);

    for (std::shared_ptr<Client> client: this->clients)
        if (client->getUsername() == username)
            return (client);
    return (nullptr);
}

std::shared_ptr<Client> ClientManager::getChatting() {
    std::unique_lock<std::mutex> lock(this->mutex);

    for (std::shared_ptr<Client> client: this->clients)
        if (client->isChatting())
            return (client);
    return (nullptr);
}

void ClientManager::reset() {
    std::unique_lock<std::mutex> lock(this->mutex);

    this->transporter.reset();
    this->sceneManager.reset();
    this->clients.clear();
    this->eventManager.reset();
    this->packetManager.reset();
    this->self.reset();
}

void ClientManager::disconnect() {
    std::unique_lock<std::mutex> lock(this->mutex);

    this->self.reset();
    this->clients.clear();
    this->transporter.reset();
}
