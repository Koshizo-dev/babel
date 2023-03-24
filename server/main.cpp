#include "entities/AsioServer.hpp"
#include "entities/SqlDatabase.hpp"
#include "../protocol/server/ServerPacketManager.hpp"

#include <iostream>
#include <memory>
#include <string>

using namespace babel;

int main() {
    std::shared_ptr<ServerManager> serverManager = std::make_shared<ServerManager>();
    serverManager->database = std::make_shared<SqlDatabase>("babel.db");
    serverManager->database->connect();
    serverManager->database->init();

    serverManager->packetManager = std::make_shared<ServerPacketManager>(serverManager);
    serverManager->eventManager = std::make_shared<EventManager>(serverManager->packetManager);
    AsioServer server(8080, serverManager);

    server.run();

    return (0);
}
