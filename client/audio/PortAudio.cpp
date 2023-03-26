#include "PortAudio.hpp"
#include "AudioSettings.hpp"

using namespace babel;

PortAudio::PortAudio(std::shared_ptr<AudioCodec> audioCodec): _audioCodec(audioCodec) {
    Pa_Initialize();
    this->_inputParameters.device = Pa_GetDefaultInputDevice();
    this->_inputParameters.channelCount = CHANNELS;
    this->_inputParameters.sampleFormat = paFloat32;
    this->_inputParameters.suggestedLatency = Pa_GetDeviceInfo(this->_inputParameters.device)->defaultHighInputLatency;
    this->_inputParameters.hostApiSpecificStreamInfo = NULL;
}

PortAudio::~PortAudio() {
    Pa_Terminate();
}

const std::shared_ptr<AudioCodec> PortAudio::getAudioCodec() const {
    return (this->_audioCodec);
}

const std::string PortAudio::capture() {
    Pa_OpenStream(&this->_audioStream, &this->_inputParameters, NULL, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, NULL, NULL);
    float inputBuffer[FRAMES_PER_BUFFER * CHANNELS];
    Pa_ReadStream(this->_audioStream, inputBuffer, FRAMES_PER_BUFFER);

    return (this->_audioCodec->encode(inputBuffer));
}

const void PortAudio::write(DecodedAudio &audio) {
    Pa_OpenStream(&this->_audioStream, &this->_inputParameters, NULL, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, NULL, NULL);
    Pa_StartStream(this->_audioStream);

    // Write the decoded audio data to the output stream
    Pa_WriteStream(this->_audioStream, audio.buffer, audio.bufferSize);

    Pa_StopStream(this->_audioStream);
    Pa_CloseStream(this->_audioStream);
}
