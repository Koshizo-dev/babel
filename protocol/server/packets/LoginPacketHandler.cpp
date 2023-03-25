#include "LoginPacketHandler.hpp"
#include "../../../server/ServerManager.hpp"
#include "../../packets/LoginErrorPacket.hpp"

#include <algorithm>
#include <iostream>
#include <typeinfo>

using namespace babel;

std::string trim(const std::string& s) {
    auto start = std::find_if_not(s.begin(), s.end(), [](int c) { return std::isspace(c); });
    auto end = std::find_if_not(s.rbegin(), s.rend(), [](int c) { return std::isspace(c); }).base();
    return (start >= end ? "" : std::string(start, end));
}

bool containsChar(const std::string& str, char ch) {
    return str.find(ch) != std::string::npos;
}

void LoginPacketHandler::handle(Packet &packet, std::shared_ptr<ServerManager> serverManager, IoClient *origin) {
    try {
        LoginPacket &loginPacket = dynamic_cast<LoginPacket&>(packet);
        std::string username = trim(loginPacket.getUsername());
        std::transform(username.begin(), username.end(), username.begin(), ::tolower);

        if (username == "")
            return (origin->getTransporter()->sendMessage(LoginErrorPacket("Username cannot be empty!").serialize()));
        if (containsChar(username, ' '))
            return (origin->getTransporter()->sendMessage(LoginErrorPacket("Username cannot contain spaces!").serialize()));
        if (serverManager->usernameExists(username))
            return (origin->getTransporter()->sendMessage(LoginErrorPacket("Someone with this username is already connected !").serialize()));

        origin->username = username;
        origin->getTransporter()->sendMessage(LoginPacket(username).serialize());
    } catch (std::bad_cast) {}
}
