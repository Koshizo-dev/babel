#include "LoginPacketHandler.hpp"
#include "../../../client/ClientManager.hpp"
#include "../../../client/scenes/MainScene.hpp"

#include <iostream>
#include <typeinfo>

using namespace babel;

void LoginPacketHandler::handle(Packet &packet, std::shared_ptr<ClientManager> clientManager) {
    try {
        LoginPacket &loginPacket = dynamic_cast<LoginPacket&>(packet);

        clientManager->self = std::shared_ptr<Client>(new Client(loginPacket.getUsername()));
        clientManager->sceneManager->setScene(new MainScene(clientManager));
    } catch (std::bad_cast) {}
}
