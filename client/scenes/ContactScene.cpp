#include "ContactScene.hpp"
#include "../ClientError.hpp"
#include <iostream>
#include <qnamespace.h>
#include <qsizepolicy.h>

using namespace babel;

ContactScene::ContactScene(std::shared_ptr<ClientManager> clientManager) {
    if (clientManager == nullptr)
        throw ClientError("Whilst initializing ContactScene: ClientManager cannot be null !");
    this->_clientManager = clientManager;
    this->_initWidgets();
    this->_initLayouts();
    this->_placeWidgets();
    this->clear();
}

ContactScene::~ContactScene() {
}

const std::string ContactScene::getName() const {
    return "Contact menu";
}

const void ContactScene::display() {
    this->_parent->show();
    this->_scrollArea->show();
}

const void ContactScene::clear() {
    this->_parent->hide();
}

const void ContactScene::refresh() {
    this->_parent->repaint();
}

const void ContactScene::handleEvent(Event &event) {
    switch (event.type) {
        case Event::NEW_CONTACT:
        {
            std::shared_ptr<Client> newContact = event.data.newContact.contact;
            Contact *contact = this->_generateContact(newContact);
            this->_contacts.insert(this->_contacts.begin(), contact);
            this->_contactsLayout->insertWidget(0, contact->getButton(), 0, Qt::AlignTop);
        }
        case Event::NEW_CHATTING:
        {
            for (auto *contact: this->_contacts)
                if (contact->getClient() == event.data.newChatting.previousClient || contact->getClient() == event.data.newChatting.newClient)
                    contact->updateChatting();
            break;
        }
        case Event::CONTACT_FILTER_UPDATE:
        {       
            std::string contactFilter = event.data.contactFilter.filter;

            for (auto *contact: this->_contacts) {
                if (contact->getClient()->getUsername().substr(0, contactFilter.size()) != contactFilter)
                    contact->getButton()->hide();
                else
                    contact->getButton()->show();
            }
        }
        default: break;
    }
}

const std::shared_ptr<SceneManager> ContactScene::getSceneManager() const {
    return (this->_clientManager->sceneManager);
}

QWidget *ContactScene::getWidget() {
    return (this->_scrollArea);
}

const void ContactScene::_initLayouts() {
    this->_contactsLayout = new QVBoxLayout(this->_parent);
}

const void ContactScene::_initWidgets() {
    this->_scrollArea = new QScrollArea();
    this->_parent = new QWidget();

    for (auto client: this->_clientManager->clients) {
        auto *contact = this->_generateContact(client);
        this->_contacts.push_back(contact);
    }

    // sort the contacts by message timestamps
    std::sort(this->_contacts.begin(), this->_contacts.end(),
              [](const Contact *a, const Contact *b) { 
            long aTimestamp = 0;
            if (a->getClient()->getMessages().size() != 0)
                aTimestamp = a->getClient()->getMessages()[a->getClient()->getMessages().size()-1]->getTimestamp();
            long bTimestamp = 0;
            if (b->getClient()->getMessages().size() != 0)
                bTimestamp = b->getClient()->getMessages()[b->getClient()->getMessages().size()-1]->getTimestamp();
            return aTimestamp > bTimestamp;
        });
}

const void ContactScene::_placeWidgets() {
    this->_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->_scrollArea->setWidget(this->_parent);
    this->_scrollArea->setWidgetResizable(true);
    this->_parent->setFixedWidth(364);
    this->_scrollArea->setFixedHeight(555);

    this->_contactsLayout->setMargin(0);
    this->_contactsLayout->setSpacing(5);

    for (auto *contact: this->_contacts) {
        this->_contactsLayout->addWidget(contact->getButton(), 0, Qt::AlignTop);
    }

    this->_contactsLayout->addStretch();

    this->refresh();
}

Contact *ContactScene::_generateContact(std::shared_ptr<Client> client) {
    Contact *contact = new Contact(client);

    QObject::connect(contact->getButton(), &QPushButton::clicked, [=]() {
        if (contact->getClient()->isChatting())
            return;
        auto previousChatting = this->_clientManager->getChatting();
        if (previousChatting != nullptr)
            previousChatting->setChatting(false);
        contact->getClient()->setChatting(true);
        contact->getClient()->setInCall(false);

        Event filterEvent(Event::CONTACT_FILTER_UPDATE);
        new (&filterEvent.data.contactFilter) Event::ContactFilterUpdate({""});
        this->getSceneManager()->getScene()->handleEvent(filterEvent);

        Event event(Event::NEW_CHATTING);
        auto data = new (&event.data.newChatting) Event::NewChatting({previousChatting, contact->getClient()});

        this->getSceneManager()->getScene()->handleEvent(event);

    });
    return (contact);
}
