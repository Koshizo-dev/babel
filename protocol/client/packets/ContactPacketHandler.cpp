#include "ContactPacketHandler.hpp"
#include "../../../client/ClientManager.hpp"
#include "../../../client/scenes/Scene.hpp"
#include "../../packets/ContactPacket.hpp"

#include <iostream>
#include <typeinfo>

using namespace babel;

const void ContactPacketHandler::handle(Packet &packet, std::shared_ptr<ClientManager> clientManager) const {
    try {
        ContactPacket &contactPacket = dynamic_cast<ContactPacket&>(packet);
        if (contactPacket.getUsername() == "")
            return;

        std::shared_ptr<Client> newContact = std::shared_ptr<Client>(new Client(contactPacket.getUsername()));

        clientManager->clients.push_back(newContact);

        Event event(Event::NEW_CONTACT);
        new (&event.data.newContact) Event::NewContact({newContact});
        clientManager->sceneManager->getScene()->handleEvent(event);
    } catch (std::bad_cast) {}
}
