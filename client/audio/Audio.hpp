#pragma once

#include "AudioCodec.hpp"

#include <memory>

namespace babel {

    class Audio {
        public:
            virtual ~Audio() {}

            virtual const std::shared_ptr<AudioCodec> getAudioCodec() const = 0;
            virtual const std::string capture() = 0;
            virtual const void write(DecodedAudio &audio) = 0;
    };
    
}
