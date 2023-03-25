#include "ContactPacketHandler.hpp"
#include "../../../server/ServerManager.hpp"
#include "../../packets/ContactPacket.hpp"

#include <algorithm>
#include <typeinfo>

using namespace babel;

const void ContactPacketHandler::handle(Packet &packet, std::shared_ptr<ServerManager> serverManager, IoClient *origin) const {
    try {
        ContactPacket &contactPacket = dynamic_cast<ContactPacket&>(packet);
        std::string username = this->_trim(contactPacket.getUsername());

        if (username == "")
            return;
        ContactPacket newContact(username);
        origin->getTransporter()->sendMessage(newContact.serialize());
        origin->addContact(username);
    } catch (std::bad_cast) {}
}

const std::string ContactPacketHandler::_trim(const std::string& s) const {
    std::string result = s;
    result.erase(std::remove_if(result.begin(), result.end(), [](char c) { return c == ' '; }), result.end());
    return result;
}
