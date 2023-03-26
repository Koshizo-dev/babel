#pragma once

#include "DecodedAudio.hpp"

#include <string>

namespace babel {

    class AudioCodec {
        public:
            virtual ~AudioCodec() {}

            virtual const std::string encode(float *buffer) const = 0;
            virtual const DecodedAudio decode(std::string buffer) const = 0;
    };
    
}
