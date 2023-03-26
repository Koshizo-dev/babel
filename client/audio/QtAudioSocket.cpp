#include "QtAudioSocket.hpp"

#include <iostream>

using namespace babel;

QtAudioSocket::QtAudioSocket(unsigned int port) {
    this->_socket.bind(QHostAddress::Any, port);
}

const void QtAudioSocket::sendAudio(std::string audio, std::string hostname, unsigned int port) {
    if (hostname == "" || port == 0)
        return;
    this->_socket.writeDatagram(audio.data(), audio.length(), QHostAddress(hostname.c_str()), port);
}

const void QtAudioSocket::receiveAudio(AudioSettings &settings, Audio &audio) {
    while (settings.isRunning() && this->_socket.hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(this->_socket.pendingDatagramSize());
        // Read the audio data from the socket
        QHostAddress senderAddress;
        quint16 senderPort;
        this->_socket.readDatagram(datagram.data(), datagram.size(), &senderAddress, &senderPort);
        unsigned char* encodedBuffer = reinterpret_cast<unsigned char*>(datagram.data());
        int encodedSize = datagram.size();

        DecodedAudio decoded = audio.getAudioCodec()->decode(std::string(reinterpret_cast<char *>(encodedBuffer), encodedSize));
        audio.write(decoded);
    }
}

const unsigned int QtAudioSocket::getPort() const {
    return (this->_socket.localPort());
}
