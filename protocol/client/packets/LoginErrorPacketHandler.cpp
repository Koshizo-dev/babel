#include "LoginErrorPacketHandler.hpp"
#include "../../../client/ClientManager.hpp"
#include "../../../client/scenes/MainScene.hpp"

#include <iostream>
#include <typeinfo>

using namespace babel;

void LoginErrorPacketHandler::handle(Packet &packet, std::shared_ptr<ClientManager> clientManager) {
    try {
        LoginErrorPacket &loginPacket = dynamic_cast<LoginErrorPacket&>(packet);

        std::cerr << "Error = " << loginPacket.getError() << std::endl;
        // clientManager->eventManager->
    } catch (std::bad_cast) {}
}
