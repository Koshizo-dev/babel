#pragma once

#include "AudioSocket.hpp"

#include <QUdpSocket>

namespace babel {

    class QtAudioSocket: public AudioSocket {
        public:
            QtAudioSocket(unsigned int port);
    
            const void sendAudio(std::string audio, std::string hostname, unsigned int port) override;
            const void receiveAudio(Audio &audio) override;
            const unsigned int getPort() const override;

        private:
            QUdpSocket _socket;
    };
    
}