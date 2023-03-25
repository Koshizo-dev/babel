#include "LoginPacketHandler.hpp"
#include "../../../server/ServerManager.hpp"
#include "../../packets/LoginErrorPacket.hpp"

#include <algorithm>
#include <iostream>
#include <typeinfo>

using namespace babel;

const void LoginPacketHandler::handle(Packet &packet, std::shared_ptr<ServerManager> serverManager, IoClient *origin) const {
    try {
        LoginPacket &loginPacket = dynamic_cast<LoginPacket&>(packet);
        std::string username = this->_trim(loginPacket.getUsername());
        std::transform(username.begin(), username.end(), username.begin(), ::tolower);

        if (username == "")
            return (origin->getTransporter()->sendMessage(LoginErrorPacket("Username cannot be empty!").serialize()));
        if (this->_containsChar(username, ' '))
            return (origin->getTransporter()->sendMessage(LoginErrorPacket("Username cannot contain spaces!").serialize()));
        if (serverManager->usernameExists(username))
            return (origin->getTransporter()->sendMessage(LoginErrorPacket("Someone with this username is already connected !").serialize()));

        origin->username = username;
        origin->getTransporter()->sendMessage(LoginPacket(username).serialize());
        serverManager->login(origin);
    } catch (std::bad_cast) {}
}

const std::string LoginPacketHandler::_trim(const std::string &s) const {
    auto start = std::find_if_not(s.begin(), s.end(), [](int c) { return std::isspace(c); });
    auto end = std::find_if_not(s.rbegin(), s.rend(), [](int c) { return std::isspace(c); }).base();
    return (start >= end ? "" : std::string(start, end));
}

const bool LoginPacketHandler::_containsChar(const std::string &str, char ch) const {
    return str.find(ch) != std::string::npos;
}
