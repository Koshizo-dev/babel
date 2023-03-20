#pragma once

#include "Message.hpp"
#include "entities/Icon.hpp"

#include <string>

namespace babel {

    class Client {
        public:
            Client(std::string username);

            std::string getUsername();
            std::shared_ptr<Icon> getIcon();
            std::shared_ptr<Icon> getNewIcon(int size = 64);
            std::vector<std::shared_ptr<Message>> getMessages();
            bool isChatting();
            bool isInCall();
            bool isChatWindow();

            void setChatting(bool isChatting);
            void setInCall(bool isInCall);
            void setChatWindow(bool isChatWindow);
            void setMessages(std::vector<std::shared_ptr<Message>> messages);

        private:
            std::string _username = "Koshizo"; // Easter egg since, not able to have capitals
            std::shared_ptr<Icon> _icon = nullptr;
            bool _isChatting = false;
            bool _isInCall = false;
            bool _isChatWindow = false;
            std::vector<std::shared_ptr<Message>> _messages = {};

            std::shared_ptr<Icon> _generateIcon(int size); // Must be called in constructor
    };

} // namespace babel
