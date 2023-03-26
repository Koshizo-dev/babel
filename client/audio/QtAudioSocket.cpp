#include "QtAudioSocket.hpp"

using namespace babel;

QtAudioSocket::QtAudioSocket(unsigned int port) {
    this->_socket.bind(QHostAddress::Any, port);
}

const void QtAudioSocket::sendAudio(std::string audio, std::string hostname, unsigned int port) {
    this->_socket.writeDatagram(audio.data(), audio.length(), QHostAddress(hostname.c_str()), port);
}

const void QtAudioSocket::receiveAudio(Audio &audio) {
    while (this->_socket.hasPendingDatagrams()) {
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
