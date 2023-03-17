#include "NamedTextField.hpp"

using namespace babel;

NamedTextField::NamedTextField(std::string name, std::shared_ptr<QWidget> parent): NamedTextField(name, parent, 0.0) {
}

NamedTextField::NamedTextField(std::string name, std::shared_ptr<QWidget> parent, double modifier) {
    this->_parent = parent;
    // Create a new QLineEdit and QLabel object
    this->_input = std::unique_ptr<QLineEdit>(new QLineEdit(this->_parent.get()));
    if (modifier != 0.0)
        this->_input->setMaximumWidth(this->_parent->width() * modifier);
    this->_label = std::unique_ptr<QLabel>(new QLabel(std::string(name + ": ").c_str(), this->_parent.get()));

    // Create a QHBoxLayout object to hold the QLineEdit and QLabel objects
    this->_layout = std::unique_ptr<QHBoxLayout>(new QHBoxLayout);
    this->_layout->addWidget(this->_label.get());
    this->_layout->addWidget(this->_input.get());
    this->_layout->addStretch();   
}

NamedTextField::~NamedTextField() {
    this->_input.reset();
    this->_label.reset();
    this->_layout.reset();
}

QHBoxLayout *NamedTextField::getLayout() {
    return (this->_layout.get());
}
