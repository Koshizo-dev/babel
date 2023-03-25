#include "SearchScene.hpp"
#include "../ClientError.hpp"
#include "../../protocol/packets/ContactPacket.hpp"

#include <iostream>

using namespace babel;

SearchScene::SearchScene(std::shared_ptr<ClientManager> clientManager) {
    if (clientManager == nullptr)
        throw ClientError("Whilst initializing SearchScene: ClientManager cannot be null !");
    this->_clientManager = clientManager;
    this->_initWidgets();
    this->_initLayouts();
    this->_placeWidgets();
    this->clear();
}

SearchScene::~SearchScene() {
}

const std::string SearchScene::getName() const {
    return "Search menu";
}

const void SearchScene::display() {
}

const void SearchScene::clear() {
}

const void SearchScene::refresh() {
}

const void SearchScene::handleEvent(Event &event) {
    if (event.type != Event::CONTACT_FILTER_UPDATE)
        return;
    auto newFilter = event.data.contactFilter.filter;

    this->_searchInput->setText(newFilter.c_str());
}

const std::shared_ptr<SceneManager> SearchScene::getSceneManager() const {
    return (this->_clientManager->sceneManager);
}

QLayout *SearchScene::getLayout() {
    return (this->_searchLayout);
}

const void SearchScene::_initLayouts() {
    this->_searchLayout = new QHBoxLayout();
}

const void SearchScene::_initWidgets() {
    this->_searchInput = new QLineEdit();
    this->_searchInput->setPlaceholderText("Find an user.");

    QObject::connect(this->_searchInput, &QLineEdit::textChanged, [=]() {
        Event filterEvent(Event::CONTACT_FILTER_UPDATE);
        new (&filterEvent.data.contactFilter) Event::ContactFilterUpdate({this->_searchInput->text().toStdString()});
        this->getSceneManager()->getScene()->handleEvent(filterEvent);
    });

    QObject::connect(this->_searchInput, &QLineEdit::returnPressed, [=]() {
        std::string username = this->_searchInput->text().toStdString();
        this->_searchInput->setText("");

        Event filterEvent(Event::CONTACT_FILTER_UPDATE);
        new (&filterEvent.data.contactFilter) Event::ContactFilterUpdate({this->_searchInput->text().toStdString()});
        this->getSceneManager()->getScene()->handleEvent(filterEvent);

        std::shared_ptr<Client> target = this->_clientManager->getClient(username);
        if (target != nullptr) {
            auto previousChatting = this->_clientManager->getChatting();
            if (previousChatting != nullptr)
                previousChatting->setChatting(false);
            target->setChatting(true);
            Event event(Event::NEW_CHATTING);
            new (&event.data.newChatting) Event::NewChatting({previousChatting, target});
            this->getSceneManager()->getScene()->handleEvent(event);
            return;
        }
        ContactPacket packet(username);
        this->_clientManager->transporter->sendMessage(packet.serialize());
    });
}

const void SearchScene::_placeWidgets() {
    this->_searchLayout->addWidget(this->_searchInput);
}
