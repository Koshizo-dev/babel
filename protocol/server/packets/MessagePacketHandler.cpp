#include "MessagePacketHandler.hpp"
#include "../../../server/ServerManager.hpp"
#include "../../packets/MessagePacket.hpp"

#include <algorithm>
#include <iostream>
#include <typeinfo>

using namespace babel;

void MessagePacketHandler::handle(Packet &packet, std::shared_ptr<ServerManager> serverManager, IoClient *origin) {
    try {
        MessagePacket &messagePacket = dynamic_cast<MessagePacket&>(packet);
        std::string content = this->_trim(messagePacket.getContent());

        if (content == "")
            return;
        serverManager->sendMessage(origin, messagePacket.getRecipient(), messagePacket.getContent());
    } catch (std::bad_cast) {}
}

std::string MessagePacketHandler::_trim(const std::string& s) {
    auto start = std::find_if_not(s.begin(), s.end(), [](int c) { return std::isspace(c); });
    auto end = std::find_if_not(s.rbegin(), s.rend(), [](int c) { return std::isspace(c); }).base();
    return (start >= end ? "" : std::string(start, end));
}

