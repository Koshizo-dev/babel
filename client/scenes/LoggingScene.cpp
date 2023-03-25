#include "LoggingScene.hpp"
#include "../ClientError.hpp"
#include "../utils.hpp"
#include "MainScene.hpp"

#include "../network/Transporter.hpp"
#include "../network/QtSocket.hpp"
#include "../../protocol/packets/LoginPacket.hpp"

#include <QLineEdit>
#include <iostream>

using namespace babel;

LoggingScene::LoggingScene(std::shared_ptr<ClientManager> clientManager) {
    if (clientManager == nullptr)
        throw ClientError("Whilst initializing LoggingScene: ClientManager cannot be null !");
    this->_clientManager = clientManager;
    this->_initLayouts();
    this->_initWidgets();
    this->_placeWidgets();
    this->clear();
}

LoggingScene::~LoggingScene() {
    this->_widget->deleteLater();
}

std::string LoggingScene::getName() {
    return "Logging menu";
}

void LoggingScene::display() {
    this->_widget->show();
}

void LoggingScene::clear() {
    this->_widget->hide();
}

void LoggingScene::refresh() {
}

void LoggingScene::handleEvent(Event &event) {
    if (event.type == Event::LOGIN_FAILED) {
        std::cerr << "login failed: [" << event.data.loginFailed.errorMessage << "]" << std::endl;
        this->_loggingAction = false;
        // TODO
    }
}

std::shared_ptr<SceneManager> LoggingScene::getSceneManager() {
    return (this->_clientManager->sceneManager);
}

void LoggingScene::_loggingButtonClicked() {
    if (this->_loggingAction) {
        return;
    }

    this->_loggingAction = true;
    // TODO Not close the transporter if same hostname + port
    std::string hostname = this->_serverField->getValue();
    unsigned int port = std::stoi(this->_portField->getValue());

    this->_clientManager->transporter = std::make_shared<Transporter>(this->_clientManager->eventManager, std::make_unique<QtSocket>(hostname, port));

    if (this->_clientManager->transporter->awaitingConnection()) {
        LoginPacket packet(this->_usernameField->getValue());
        this->_clientManager->transporter->sendMessage(packet.serialize());
    } else {
        std::cerr << "[DEBUG] Could not connect to server" << std::endl;
        // TODO show  error message under
        this->_loggingAction = false;
    }
}

void LoggingScene::_initLayouts() {
    this->_layout = new QVBoxLayout();
    this->_topLayout = new QHBoxLayout();
}

void LoggingScene::_initWidgets() {
    this->_widget = new QWidget(this->getSceneManager()->getWidget());

    this->_loggingButton = new QPushButton("Login");
    this->_loggingButton->setGeometry(0, 0, 200, 100);
   
    this->_usernameField = new NamedTextField("Username", this->_widget);
    this->_serverField = new NamedTextField("Server", this->_widget);
    this->_serverField->setValue("127.0.0.1");
    this->_portField = new NamedTextField("Port", this->_widget, 0.7);
    this->_portField->setValue("8080");
}

void LoggingScene::_placeWidgets() {
    this->_topLayout->addLayout(this->_usernameField->getLayout());
    this->_topLayout->addLayout(this->_serverField->getLayout());
    this->_topLayout->addLayout(this->_portField->getLayout());
    this->_layout->addLayout(this->_topLayout);
    this->_layout->addWidget(this->_loggingButton);

    // Set the layout for the parent widget
    this->_widget->setLayout(this->_layout);
    // Set the size of the widget and move it to the center of the parent
    this->_widget->setFixedSize(this->_widget->sizeHint());
    this->_widget->move((this->getSceneManager()->getWidget()->width() - this->_widget->width()) / 2, (this->getSceneManager()->getWidget()->height() - this->_widget->height()) / 2);

    QObject::connect(this->_loggingButton, &QPushButton::clicked, [=]() {
       this->_loggingButtonClicked(); 
    });
}
