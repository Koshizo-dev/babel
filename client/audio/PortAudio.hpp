#pragma once

#include "Audio.hpp"

#include <portaudio.h>

namespace babel {

    class PortAudio: public Audio {
        public:
            PortAudio(std::shared_ptr<AudioCodec> encoder);
            ~PortAudio() override;

            const std::shared_ptr<AudioCodec> getAudioCodec() const override;
            const std::string capture() override;
            const void write(DecodedAudio &audio) override;

        private:
            const std::shared_ptr<AudioCodec> _audioCodec;
            PaStream *_audioStream;
            PaStreamParameters _inputParameters;
    };
    
}
