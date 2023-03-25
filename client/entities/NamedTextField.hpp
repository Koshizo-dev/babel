#pragma once

#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QWidget>

namespace babel {
    class NamedTextField {
        public:
            NamedTextField(std::string name, QWidget* parent);
            NamedTextField(std::string name, QWidget* parent, double modifier);
            ~NamedTextField();

            QHBoxLayout *getLayout() const;
            const void setValue(std::string value);
            const std::string getValue() const;

        private:
            QWidget *_parent = nullptr;
            QHBoxLayout *_layout = nullptr;
            QLineEdit *_input = nullptr;
            QLabel *_label = nullptr;
    };
}
