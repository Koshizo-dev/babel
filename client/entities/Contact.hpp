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
    
            const std::shared_ptr<Client> getClient() const;
            QPushButton *getButton() const;
            QLabel *getButtonLabel() const;
            QHBoxLayout *getButtonLayout() const;
            const void updateChatting() const;

        private:
            const void _joinElements();
            const void _initElements();

            QPushButton *_button = nullptr;
            QLabel *_buttonLabel = nullptr;
            QHBoxLayout *_buttonLayout = nullptr;
            std::shared_ptr<Client> _client = nullptr;
    };
    
}
