#include "ClientManager.hpp"
#include "audio/PortAudio.hpp"
#include "audio/OpusCodec.hpp"
#include "displays/QDisplay.hpp"
#include "audio/QtAudioSocket.hpp"
#include <QApplication>
#include <QPushButton>
#include <QFontDatabase>

#include <QtPlugin>

#include "../protocol/packets/LoginPacket.hpp"
#include "../protocol/PacketManager.hpp"

#if (WIN32 || _WIN32 || __WIN32__ || WIN64 || __WIN64__)
    Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
#else
    Q_IMPORT_PLUGIN(QXcbIntegrationPlugin)
#endif

using namespace babel;

int main(int argc, char **argv) {
    std::shared_ptr<ClientManager> clientManager = std::shared_ptr<ClientManager>(new ClientManager());
    clientManager->packetManager = std::make_shared<ClientPacketManager>(clientManager);
    clientManager->eventManager = std::make_shared<EventManager>(clientManager, clientManager->packetManager);

    clientManager->audioSettings = std::make_shared<AudioSettings>();
    clientManager->audioSocket = std::make_shared<QtAudioSocket>(0);
    std::shared_ptr<AudioCodec> audioCodec = std::make_shared<OpusCodec>();
    clientManager->audioDevice = std::make_shared<PortAudio>(audioCodec);

    DisplaySettings settings(argc, argv, "Babel | New Gen", 1280, 720);
    Display *display = new QDisplay(settings, clientManager);

    int code = display->run();

    clientManager->reset();
    delete display;
    return (code);
}
