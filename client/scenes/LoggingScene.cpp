#include "LoggingScene.hpp"
#include "../ClientError.hpp"
#include "../utils.hpp"

#include <qnamespace.h>
#include <qobject.h>
#include <QLineEdit>
#include <iostream>
#include <qtextlayout.h>
#include <qwidget.h>

using namespace babel;

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

// Load the Scene with the parent passed as parameter
// If function already loaded
//     Will call the Scene::clear.
//     Will override the current parent.
void LoggingScene::load(std::shared_ptr<QWidget> parent) {
    if (this->_parent)
        this->clear();
    this->_parent = parent;
    this->_initLayouts();
    this->_initWidgets();
    this->_placeWidgets();
}

void LoggingScene::display() {
    if (this->_parent == nullptr)
        throw ClientError("LoggingScene needs to be loaded first!");

    this->_widget->setParent(this->_parent.get());
}

void LoggingScene::clear() {
    if (this->_parent == nullptr)
        throw ClientError("LoggingScene needs to be loaded first!");

    this->_widget->setParent(nullptr);
}

// Refresh the MainScene
// Mainly used when window size changed by example
// Or any variable that might have been shown on screen was updated.
void LoggingScene::refresh() {
    if (this->_parent == nullptr)
        throw ClientError("LoggingScene needs to be loaded first!");
}

void LoggingScene::_loggingButtonClicked() {
    if (this->_loggingAction) {
        return;
    }

    this->_loggingAction = true;
    std::cerr << "[DEBUG] Sending request to connect to server" << std::endl;
    // TODO Connection packet to server
}

void LoggingScene::_initLayouts() {
    this->_layout = std::unique_ptr<QBoxLayout>(new QVBoxLayout());
    this->_topLayout = std::unique_ptr<QBoxLayout>(new QHBoxLayout());
}

void LoggingScene::_initWidgets() {
    this->_widget = std::shared_ptr<QWidget>(new QWidget());

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
    this->_widget->move((this->_parent->width() - this->_widget->width()) / 2, (this->_parent->height() - this->_widget->height()) / 2);

    QObject::connect(this->_loggingButton.get(), &QPushButton::clicked, [=]() {
       this->_loggingButtonClicked(); 
    });
}
