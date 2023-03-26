#pragma once

namespace babel {

    class DecodedAudio {
        public:
            DecodedAudio(int targetSize) {
                buffer = new float[targetSize];
            }

            ~DecodedAudio() {
                delete[] buffer;
            }

            float *buffer;
            int bufferSize;
    };
    
}
