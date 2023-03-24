#include "QtSocket.hpp"

#include <QHostAddress>
#include <QWidget>
#include <QAbstractSocket>
#include <qabstractsocket.h>

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
        this->_eventManager->handlePacket(data.toStdString());
    });
}
