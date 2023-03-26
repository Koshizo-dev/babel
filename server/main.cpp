#include "entities/AsioServer.hpp"
#include "entities/SqlDatabase.hpp"
#include "../protocol/server/ServerPacketManager.hpp"

#include <iostream>
#include <memory>
#include <string>
#include <csignal>

using namespace babel;

std::shared_ptr<ServerManager> getServerManager(std::shared_ptr<ServerManager> target) {
    static std::shared_ptr<ServerManager> serverManager = nullptr;
    if (target != nullptr)
        serverManager = target;
    return (serverManager);
}

void signalHandler(int signal) {
    std::cout << "Signal " << signal << " received. Exiting..." << std::endl;
    getServerManager(nullptr)->close();
    std::cout << "Server closed!" << std::endl;
    exit(signal);
}

int main() {
    std::shared_ptr<ServerManager> serverManager = std::make_shared<ServerManager>();
    getServerManager(serverManager);
    std::signal(SIGINT, signalHandler);
    serverManager->database = std::make_shared<SqlDatabase>("babel.db");
    serverManager->database->connect();
    serverManager->database->init();

    serverManager->packetManager = std::make_shared<ServerPacketManager>(serverManager);
    serverManager->eventManager = std::make_shared<EventManager>(serverManager->packetManager);
    AsioServer server(8080, serverManager);

    server.run();

    return (0);
}
