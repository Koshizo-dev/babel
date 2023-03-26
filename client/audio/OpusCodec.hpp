#pragma once

#include "AudioCodec.hpp"

#include <opus/opus.h>

namespace babel {

    class OpusCodec: public AudioCodec {
        public:
            OpusCodec();
            ~OpusCodec() override;

            const std::string encode(float *buffer) const override;
            const DecodedAudio decode(std::string buffer) const override;

        private:
            OpusEncoder *_encoder = nullptr;
            OpusDecoder *_decoder = nullptr;
    };
    
}
