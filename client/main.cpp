#include "ClientManager.hpp"
#include "audio/PortAudio.hpp"
#include "audio/OpusCodec.hpp"
#include "displays/QDisplay.hpp"
#include <QApplication>
#include <QPushButton>
#include <QFontDatabase>

#include <QtPlugin>

#include "../protocol/packets/LoginPacket.hpp"
#include "../protocol/PacketManager.hpp"

Q_IMPORT_PLUGIN(QXcbIntegrationPlugin);

using namespace babel;

int main(int argc, char **argv) {
    std::shared_ptr<ClientManager> clientManager = std::shared_ptr<ClientManager>(new ClientManager());
    clientManager->packetManager = std::make_shared<ClientPacketManager>(clientManager);
    clientManager->eventManager = std::make_shared<EventManager>(clientManager, clientManager->packetManager);

    std::shared_ptr<AudioCodec> audioCodec = std::make_shared<OpusCodec>();
    clientManager->audioDevice = std::make_shared<PortAudio>(audioCodec);

    DisplaySettings settings(argc, argv, "Babel | New Gen", 1280, 720);
    Display *display = new QDisplay(settings, clientManager);

    int code = display->run();

    clientManager->reset();
    delete display;
    return (code);
}
