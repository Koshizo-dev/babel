#include "ClientManager.hpp"
#include "Client.hpp"
#include "audio/QtAudioSocket.hpp"

using namespace babel;

const std::shared_ptr<Client> ClientManager::getClient(std::string username) const {
    for (std::shared_ptr<Client> client: this->clients)
        if (client->getUsername() == username)
            return (client);
    return (nullptr);
}

const std::shared_ptr<Client> ClientManager::getChatting() const {
    for (std::shared_ptr<Client> client: this->clients)
        if (client->isChatting())
            return (client);
    return (nullptr);
}

const void ClientManager::reset() {
    this->transporter.reset();
    this->sceneManager.reset();
    this->clients.clear();
    this->eventManager.reset();
    this->packetManager.reset();
    this->self.reset();
}

const void ClientManager::disconnect() {
    this->self.reset();
    this->clients.clear();
    this->transporter.reset();
    this->stopAudioSocket();
}

const void ClientManager::startAudioSocket() {
    this->stopAudioSocket();
    this->audioSettings->setRunning(true);
    this->_sendAudioThread = new std::thread(&ClientManager::_sendAudio, this);
    this->_receiveAudioThread = new std::thread(&ClientManager::_receiveAudio, this);
}

const void ClientManager::_receiveAudio() {
    while (this->audioSettings->isRunning()) {
        if (this->audioSocket == nullptr)
            return;
        this->audioSocket->receiveAudio(*this->audioSettings, *this->audioDevice);
    }
}

const void ClientManager::_sendAudio() {
    while (this->audioSettings->isRunning()) {
        if (this->audioSocket == nullptr)
            return;
        AudioReceiver receiver = this->audioSettings->getReceiver();
        this->audioSocket->sendAudio(this->audioDevice->capture(), receiver.hostname, receiver.port);
    }
}

const void ClientManager::stopAudioSocket() {
    if (!this->audioSettings->isRunning())
        return;
    this->audioSettings->setRunning(false);

    if (this->_sendAudioThread)
        this->_sendAudioThread->join();
    if (this->_receiveAudioThread)
        this->_receiveAudioThread->join();
}
