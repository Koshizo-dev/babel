#include "LoginPacketHandler.hpp"

#include <iostream>
#include <typeinfo>

using namespace babel;

void LoginPacketHandler::handle(Packet &packet, std::shared_ptr<ClientManager> clientManager) {
    try {
        LoginPacket &loginPacket = dynamic_cast<LoginPacket&>(packet);
        std::cout << "Hello user: [" << loginPacket.getUsername() << "] !" << std::endl;
    } catch (std::bad_cast) {}
}
