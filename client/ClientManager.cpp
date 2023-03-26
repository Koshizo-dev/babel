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
}

const void ClientManager::startAudioSocket() {
    this->stopAudioSocket();
    this->_audioThread = new std::thread(&ClientManager::_initAudioSocket, this);
}

const void ClientManager::_initAudioSocket() {
    this->_audioMutex.lock();
    this->_isAudioSocketRunning = true;
    this->_audioMutex.unlock();

    while (true) {
        this->_audioMutex.lock();
        if (!this->_isAudioSocketRunning) {
            this->_audioMutex.unlock();
            break;
        }
        this->_audioMutex.unlock();
        // AudioReceiver receiver = this->audioSettings->getReceiver();
        // socket->sendAudio(this->audioDevice->capture(), receiver.hostname, receiver.port);
        // socket->receiveAudio(*this->audioDevice);
    }
}

const void ClientManager::stopAudioSocket() {
    if (this->_audioThread == nullptr || !this->_isAudioSocketRunning)
        return;

    this->_audioMutex.lock();
    this->_isAudioSocketRunning = false;
    this->_audioMutex.unlock();
    this->_audioThread->join();
}
