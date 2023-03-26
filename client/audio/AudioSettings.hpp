#pragma once

#include <mutex>

namespace babel {    
    #define SAMPLE_RATE 48000
    #define FRAMES_PER_BUFFER 480
    #define CHANNELS 2
    #define BITRATE 128000
    
    class AudioReceiver {
        public:
            AudioReceiver(std::string hostname, unsigned int port): hostname(hostname), port(port) {}

            std::string hostname;
            unsigned int port;
    };

    class AudioSettings {
        public:
            AudioSettings();
    
            const void setReceiver(AudioReceiver receiver);
            const AudioReceiver getReceiver();

        private:
            std::mutex _mutex;
            AudioReceiver _receiver;
    };

}
