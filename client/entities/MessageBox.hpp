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
            ~MessageBox();
    
            std::shared_ptr<Client> getClient();
            std::shared_ptr<QHBoxLayout> getLayout();

        private:
            void _joinElements();
            void _initElements();
            std::shared_ptr<QLabel> _generateMessage(std::shared_ptr<Message> message);

            std::vector<std::shared_ptr<QLabel>> _messageLabels = {};
            std::shared_ptr<QLabel> _userLabel = nullptr;
            std::shared_ptr<Icon> _userIcon = nullptr;
            std::shared_ptr<QHBoxLayout> _userLayout = nullptr;
            std::shared_ptr<QVBoxLayout> _messageLayout = nullptr;
            std::shared_ptr<QHBoxLayout> _layout = nullptr;

            std::shared_ptr<Client> _client = nullptr;
            std::vector<std::shared_ptr<Message>> _messages = {};
            std::vector<std::shared_ptr<QHBoxLayout>> _messageLayouts = {};
    };
    
}
