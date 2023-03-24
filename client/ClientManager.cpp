#include "ClientManager.hpp"

using namespace babel;

std::shared_ptr<Client> ClientManager::getChatting() {
    for (std::shared_ptr<Client> client: this->clients)
        if (client->isChatting())
            return (client);
    printf("none found!\n");
    return (nullptr);
}

void ClientManager::reset() {
    printf("transporter reseting!\n");
    this->transporter.reset();
    printf("1\n");
    this->sceneManager.reset();
    printf("2\n");
    this->clients.clear();
    printf("3\n");
    this->eventManager.reset();
    printf("4\n");
    this->packetManager.reset();
    printf("5\n");
    this->self.reset();
    printf("finished!\n");
}

void ClientManager::disconnect() {
    this->clients.clear();
    this->self.reset();
}
