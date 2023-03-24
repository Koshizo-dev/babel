#include "LoginPacketHandler.hpp"
#include "../../../server/ServerManager.hpp"

#include <iostream>
#include <typeinfo>

using namespace babel;

void LoginPacketHandler::handle(Packet &packet, std::shared_ptr<ServerManager> serverManager, IoClient *origin) {
    try {
        LoginPacket &loginPacket = dynamic_cast<LoginPacket&>(packet);
        std::cout << "received login packet !" << std::endl;
    } catch (std::bad_cast) {}
}
