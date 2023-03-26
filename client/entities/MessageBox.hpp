#pragma once

#include "../Client.hpp"

#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <vector>

namespace babel {

    class MessageBox {
        public:
            MessageBox(std::shared_ptr<Client> client, std::vector<std::shared_ptr<Message>> messages);

            const std::shared_ptr<Client> getClient() const;
            QLayout *getLayout() const;

        private:
            const void _joinElements();
            const void _initElements();
            QLabel *_generateMessage(std::shared_ptr<Message> message) const;

            std::vector<QLabel*> _messageLabels = {};
            QLabel *_userLabel = nullptr;
            Icon *_userIcon = nullptr;
            QHBoxLayout *_userLayout = nullptr;
            QVBoxLayout *_messageLayout = nullptr;
            QHBoxLayout *_layout = nullptr;

            std::shared_ptr<Client> _client = nullptr;
            std::vector<std::shared_ptr<Message>> _messages = {};
            std::vector<QHBoxLayout*> _messageLayouts = {};
    };
    
}
