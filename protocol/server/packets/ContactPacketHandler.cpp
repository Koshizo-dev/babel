#include "ContactPacketHandler.hpp"
#include "../../../server/ServerManager.hpp"
#include "../../packets/ContactPacket.hpp"

#include <algorithm>
#include <typeinfo>

using namespace babel;

void ContactPacketHandler::handle(Packet &packet, std::shared_ptr<ServerManager> serverManager, IoClient *origin) {
    try {
        ContactPacket &contactPacket = dynamic_cast<ContactPacket&>(packet);
        std::string username = this->_trim(contactPacket.getUsername());

        if (username == "")
            return;
        ContactPacket newContact(username);
        origin->getTransporter()->sendMessage(newContact.serialize());
    } catch (std::bad_cast) {}
}

std::string ContactPacketHandler::_trim(const std::string& s) {
    std::string result = s;
    result.erase(std::remove_if(result.begin(), result.end(), [](char c) { return c == ' '; }), result.end());
    return result;
}

