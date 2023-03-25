#include "NamedTextField.hpp"

using namespace babel;

NamedTextField::NamedTextField(std::string name, QWidget *parent): NamedTextField(name, parent, 0.0) {
}

NamedTextField::NamedTextField(std::string name, QWidget *parent, double modifier) {
    this->_parent = parent;
    // Create a new QLineEdit and QLabel object
    this->_input = new QLineEdit();
    if (modifier != 0.0)
        this->_input->setMaximumWidth(this->_parent->width() * modifier);
    this->_label = new QLabel(std::string(name + ": ").c_str());

    // Create a QHBoxLayout object to hold the QLineEdit and QLabel objects
    this->_layout = new QHBoxLayout;
    this->_layout->addWidget(this->_label);
    this->_layout->addWidget(this->_input);
    this->_layout->addStretch();
}

NamedTextField::~NamedTextField() {
}

QHBoxLayout *NamedTextField::getLayout() const {
    return (this->_layout);
}

const void NamedTextField::setValue(std::string value) {
    this->_input->setText(value.c_str());
}

const std::string NamedTextField::getValue() const {
    return (this->_input->text().toStdString());
}
