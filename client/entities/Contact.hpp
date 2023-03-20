#pragma once

#include "../Client.hpp"

#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>

namespace babel {

    class Contact {
        public:
            Contact(std::shared_ptr<Client> client);
            ~Contact();
    
            std::shared_ptr<Client> getClient();
            std::shared_ptr<QPushButton> getButton();
            std::shared_ptr<QLabel> getButtonLabel();
            std::shared_ptr<QHBoxLayout> getButtonLayout();

        private:
            void _joinElements();
            void _initElements();

            std::shared_ptr<QPushButton> _button = nullptr;
            std::shared_ptr<QLabel> _buttonLabel = nullptr;
            std::shared_ptr<QHBoxLayout> _buttonLayout = nullptr;
            std::shared_ptr<Client> _client = nullptr;
    };
    
}
