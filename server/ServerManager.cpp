#include "ServerManager.hpp"
#include <algorithm>

using namespace babel;

bool ServerManager::usernameExists(const std::string &target) {
    return std::any_of(clients.begin(), clients.end(), [&](const std::shared_ptr<IoClient> &client) {
        return client->username == target;
    });
}
