#include "LoggingScene.hpp"
#include "../ClientError.hpp"
#include "../utils.hpp"

#include <qobject.h>
#include <QLineEdit>
#include <iostream>
#include <qtextlayout.h>

using namespace babel;

LoggingScene::~LoggingScene() {
    this->_loggingButton.reset();
    this->_usernameInput.reset();
    this->_usernameLabel.reset();
    this->_usernameLayout.reset();
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
}

void LoggingScene::display() {
    if (this->_parent == nullptr)
        throw ClientError("LoggingScene needs to be loaded first!");

    this->_loggingButton = std::unique_ptr<QPushButton>(new QPushButton("Login", this->_parent.get()));
    this->_loggingButton->setGeometry(0, 0, 200, 100);

    // Create a new QLineEdit and QLabel object
    this->_usernameInput = std::unique_ptr<QLineEdit>(new QLineEdit(this->_parent.get()));
    this->_usernameInput->setMaximumWidth(this->_parent->width() * 0.2);

    this->_usernameLabel = std::unique_ptr<QLabel>(new QLabel("Email: ", this->_parent.get()));

    // Create a QHBoxLayout object to hold the QLineEdit and QLabel objects
    this->_usernameLayout = std::unique_ptr<QHBoxLayout>(new QHBoxLayout);
    this->_usernameLayout->addWidget(this->_usernameLabel.get());
    this->_usernameLayout->addWidget(this->_usernameInput.get());
    this->_usernameLayout->addStretch();
    
    // Set the layout for the parent widget
    this->_parent->setLayout(this->_usernameLayout.get());

    int x = centerX(this->_parent.get(), this->_loggingButton->width());
    int y = centerY(this->_parent.get(), this->_loggingButton->height());
    this->_loggingButton->move(x, y);


    QObject::connect(this->_loggingButton.get(), &QPushButton::clicked, [=]() {
       this->_loggingButtonClicked(); 
    });
}

void LoggingScene::_loggingButtonClicked() {
    if (this->_loggingAction) {
        return;
    }
    this->_loggingAction = true;
    std::cerr << "[DEBUG] Sending request to connect to server" << std::endl;
    // TODO Connection packet to server
}

void LoggingScene::clear() {
    if (this->_parent == nullptr)
        throw ClientError("LoggingScene needs to be loaded first!");
}

// Refresh the MainScene
// Mainly used when window size changed by example
// Or any variable that might have been shown on screen was updated.
void LoggingScene::refresh() {
    if (this->_parent == nullptr)
        throw ClientError("LoggingScene needs to be loaded first!");
}
