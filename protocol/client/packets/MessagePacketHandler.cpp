#include "MessagePacketHandler.hpp"
#include "../../../client/ClientManager.hpp"
#include "../../packets/MessagePacket.hpp"

#include <iostream>
#include <typeinfo>

using namespace babel;

void MessagePacketHandler::handle(Packet &packet, std::shared_ptr<ClientManager> clientManager) {
    try {
        MessagePacket &messagePacket = dynamic_cast<MessagePacket&>(packet);

        std::cout << "{" << messagePacket.getTimestamp() << "}: sender = [" << messagePacket.getSender() << "] | recipient = [" << messagePacket.getRecipient() << "]" << std::endl;
        std::cout << "[" << messagePacket.getContent() << "]" << std::endl;

    } catch (std::bad_cast) {}
}
