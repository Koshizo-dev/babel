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
    
            std::shared_ptr<Client> getClient() const;
            QPushButton *getButton();
            QLabel *getButtonLabel();
            QHBoxLayout *getButtonLayout();
            void updateChatting();

        private:
            void _joinElements();
            void _initElements();

            QPushButton *_button = nullptr;
            QLabel *_buttonLabel = nullptr;
            QHBoxLayout *_buttonLayout = nullptr;
            std::shared_ptr<Client> _client = nullptr;
    };
    
}
