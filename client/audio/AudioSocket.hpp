#pragma once

#include "Audio.hpp"
#include "AudioSettings.hpp"

#include <string>

namespace babel {

    class AudioSocket {
        public:
            virtual const void sendAudio(std::string audio, std::string hostname, unsigned int port) = 0;
            virtual const void receiveAudio(AudioSettings &settings, Audio &audio) = 0;
            virtual const unsigned int getPort() const = 0;
    };
    
}
