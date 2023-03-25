#include "QtSocket.hpp"

#include <QHostAddress>
#include <QWidget>
#include <QAbstractSocket>
#include <qabstractsocket.h>
#include <sstream>

using namespace babel;

QtSocket::QtSocket(std::string hostname, unsigned int port) {
    this->_socket = std::make_unique<QTcpSocket>(new QTcpSocket());

    this->_socket->connectToHost(QHostAddress(hostname.c_str()), port);
}

bool QtSocket::awaitingConnection() {
    return (this->_socket->waitForConnected());
}

void QtSocket::closeConnection() {
    this->_socket->close();
}

bool QtSocket::flush() {
    return (this->_socket->flush());
}

void QtSocket::write(std::string message) {
    this->_socket->write(message.data(), message.length());
}

void QtSocket::setEventManager(std::shared_ptr<EventManager> eventManager) {
    this->_eventManager = eventManager;

    QAbstractSocket::connect(this->_socket.get(), &QTcpSocket::readyRead, [=]() {

    QByteArray data = this->_socket->readAll();
        std::string packetData = std::string(data.constData(), data.length());

        while (true) {
            size_t delimiterIndex = packetData.find("\r\n");
            if (delimiterIndex == std::string::npos) {
                break; // Incomplete packet, wait for more data
            }

            std::string packet = packetData.substr(0, delimiterIndex);
            this->_eventManager->handlePacket(packet);

            packetData = packetData.substr(delimiterIndex + 2);
        }
        
    });
}
