#include "LoggingScene.hpp"
#include "../ClientError.hpp"
#include "../utils.hpp"
#include "MainScene.hpp"

#include <qnamespace.h>
#include <qobject.h>
#include <QLineEdit>
#include <iostream>
#include <qtextlayout.h>
#include <qwidget.h>

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
    this->_loggingButton.reset();
    this->_usernameField.reset();
    this->_serverField.reset();
    this->_portField.reset();
    this->_topLayout.reset();
    this->_layout.reset();
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

// Refresh the MainScene
// Mainly used when window size changed by example
// Or any variable that might have been shown on screen was updated.
void LoggingScene::refresh() {
}

std::shared_ptr<SceneManager> LoggingScene::getSceneManager() {
    return (this->_clientManager->sceneManager);
}

void LoggingScene::_loggingButtonClicked() {
    if (this->_loggingAction) {
        return;
    }

    this->_loggingAction = true;
    this->getSceneManager()->setScene(new MainScene(this->_clientManager));
    std::cerr << "[DEBUG] Sending request to connect to server" << std::endl;
    // TODO Connection packet to server
}

void LoggingScene::_initLayouts() {
    this->_layout = std::unique_ptr<QBoxLayout>(new QVBoxLayout());
    this->_topLayout = std::unique_ptr<QBoxLayout>(new QHBoxLayout());
}

void LoggingScene::_initWidgets() {
    this->_widget = std::shared_ptr<QWidget>(new QWidget(this->getSceneManager()->getWidget().get()));

    this->_loggingButton = std::unique_ptr<QPushButton>(new QPushButton("Login"));
    this->_loggingButton->setGeometry(0, 0, 200, 100);
   
    this->_usernameField = std::unique_ptr<NamedTextField>(new NamedTextField("Username", this->_widget));
    this->_serverField = std::unique_ptr<NamedTextField>(new NamedTextField("Server", this->_widget));
    this->_portField = std::unique_ptr<NamedTextField>(new NamedTextField("Port", this->_widget, 0.7));
}

void LoggingScene::_placeWidgets() {
    this->_topLayout->addLayout(this->_usernameField->getLayout());
    this->_topLayout->addLayout(this->_serverField->getLayout());
    this->_topLayout->addLayout(this->_portField->getLayout());
    this->_layout->addLayout(this->_topLayout.get());
    this->_layout->addWidget(this->_loggingButton.get());

    // Set the layout for the parent widget
    this->_widget->setLayout(this->_layout.get());
    // Set the size of the widget and move it to the center of the parent
    this->_widget->setFixedSize(this->_widget->sizeHint());
    this->_widget->move((this->getSceneManager()->getWidget()->width() - this->_widget->width()) / 2, (this->getSceneManager()->getWidget()->height() - this->_widget->height()) / 2);

    QObject::connect(this->_loggingButton.get(), &QPushButton::clicked, [=]() {
       this->_loggingButtonClicked(); 
    });
}
