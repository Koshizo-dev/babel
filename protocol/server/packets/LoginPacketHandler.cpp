#include "LoginPacketHandler.hpp"
#include "../../../server/ServerManager.hpp"
#include "../../packets/LoginErrorPacket.hpp"

#include <algorithm>
#include <iostream>
#include <typeinfo>

using namespace babel;

void LoginPacketHandler::handle(Packet &packet, std::shared_ptr<ServerManager> serverManager, IoClient *origin) {
    try {
        LoginPacket &loginPacket = dynamic_cast<LoginPacket&>(packet);
        std::string username = loginPacket.getUsername();
        std::transform(username.begin(), username.end(), username.begin(), ::tolower);

        if (username == "")
            return (origin->getTransporter()->sendMessage(LoginErrorPacket("Username cannot be empty!").serialize()));
        if (serverManager->usernameExists(username))
            return (origin->getTransporter()->sendMessage(LoginErrorPacket("Someone with this username is already connected !").serialize()));

        origin->username = username;
        origin->getTransporter()->sendMessage(LoginPacket(username).serialize());
    } catch (std::bad_cast) {}
}
