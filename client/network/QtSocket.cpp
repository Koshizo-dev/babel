#include "QtSocket.hpp"

#include <QHostAddress>

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
    this->_socket->write(message.c_str());
}
