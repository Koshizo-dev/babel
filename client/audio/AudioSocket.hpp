#pragma once

#include "Audio.hpp"

#include <string>

namespace babel {

    class AudioSocket {
        public:
            virtual const void sendAudio(std::string audio, std::string hostname, unsigned int port) = 0;
            virtual const void receiveAudio(Audio &audio) = 0;
            virtual const unsigned int getPort() const = 0;
    };
    
}
