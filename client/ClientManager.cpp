#include "ClientManager.hpp"

using namespace babel;

std::shared_ptr<Client> ClientManager::getChatting() {
    for (std::shared_ptr<Client> client: this->clients)
        if (client->isChatting())
            return (client);
    return (nullptr);
}
