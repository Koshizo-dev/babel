#include "AudioSettings.hpp"

using namespace babel;

AudioSettings::AudioSettings(): _receiver("", 0) {
}

const void AudioSettings::setReceiver(AudioReceiver receiver) {
    std::lock_guard<std::mutex> lock(this->_mutex);
    this->_receiver = receiver;
}

const AudioReceiver AudioSettings::getReceiver() {
    return (this->_receiver);
}

const void AudioSettings::setRunning(bool isRunning) {
    std::lock_guard<std::mutex> lock(this->_mutex);
    this->_isRunning = isRunning;
}

const bool AudioSettings::isRunning() {
    std::lock_guard<std::mutex> lock(this->_mutex);
    return (this->_isRunning);
}
