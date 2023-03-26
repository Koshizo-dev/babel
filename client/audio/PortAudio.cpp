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
    this->_outputParameters.device = Pa_GetDefaultOutputDevice();
    this->_outputParameters.channelCount = CHANNELS;
    this->_outputParameters.sampleFormat = paFloat32;
    this->_outputParameters.suggestedLatency = Pa_GetDeviceInfo(this->_outputParameters.device)->defaultHighOutputLatency;
    this->_outputParameters.hostApiSpecificStreamInfo = NULL;
    Pa_OpenStream(&this->_audioStream, &this->_inputParameters, &this->_outputParameters, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, NULL, NULL);
    Pa_StartStream(this->_audioStream);
}

PortAudio::~PortAudio() {
    Pa_StopStream(this->_audioStream);
    Pa_CloseStream(this->_audioStream);
    Pa_Terminate();
}

const std::shared_ptr<AudioCodec> PortAudio::getAudioCodec() const {
    return (this->_audioCodec);
}

const std::string PortAudio::capture() {
    float inputBuffer[FRAMES_PER_BUFFER * CHANNELS];
    Pa_ReadStream(this->_audioStream, inputBuffer, FRAMES_PER_BUFFER);

    return (this->_audioCodec->encode(inputBuffer));
}

const void PortAudio::write(DecodedAudio &audio) {
    // Write the decoded audio data to the output stream
    Pa_WriteStream(this->_audioStream, audio.buffer, audio.bufferSize);
}
