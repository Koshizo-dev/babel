#include "AudioSettings.hpp"

using namespace babel;

AudioSettings::AudioSettings(): _receiver("", 0) {
}

const void AudioSettings::setReceiver(AudioReceiver receiver) {
    this->_mutex.lock();
    this->_receiver = receiver;
    this->_mutex.unlock();
}

const AudioReceiver AudioSettings::getReceiver() {
    return (this->_receiver);
}