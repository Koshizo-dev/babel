#include "OpusCodec.hpp"
#include "AudioSettings.hpp"

using namespace babel;

#define OPUS_FRAME_SIZE 960

OpusCodec::OpusCodec() {
    int error;
    this->_encoder = opus_encoder_create(SAMPLE_RATE, CHANNELS, OPUS_APPLICATION_VOIP, &error);
    opus_encoder_ctl(this->_encoder, OPUS_SET_BITRATE(BITRATE));
    this->_decoder = opus_decoder_create(SAMPLE_RATE, CHANNELS, &error);
}

OpusCodec::~OpusCodec() {
    opus_encoder_destroy(this->_encoder);
    opus_decoder_destroy(this->_decoder);
}

const std::string OpusCodec::encode(float *buffer) const {
    const int bufferSize = OPUS_FRAME_SIZE * CHANNELS * sizeof(float); 
    unsigned char outputBuffer[bufferSize];
    int encodedSize = opus_encode_float(this->_encoder, buffer, FRAMES_PER_BUFFER, outputBuffer, bufferSize);

    return (std::string(reinterpret_cast<char*>(outputBuffer), encodedSize));
}

const DecodedAudio OpusCodec::decode(std::string buffer) const {
    DecodedAudio audio(OPUS_FRAME_SIZE * CHANNELS);
    audio.bufferSize = opus_decode_float(this->_decoder, reinterpret_cast<const unsigned char *>(buffer.data()), buffer.length(), audio.buffer, OPUS_FRAME_SIZE, 0);
    return (audio);
}
