#pragma once

#include "Message.hpp"
#include "entities/Icon.hpp"

#include <string>

namespace babel {

    class Client {
        public:
            Client(std::string username);

            std::string getUsername();
            Icon *getIcon(int size = 64);
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
            bool _isChatting = false;
            bool _isInCall = false;
            bool _isChatWindow = false;
            std::vector<std::shared_ptr<Message>> _messages = {};

            Icon *_generateIcon(int size); // Must be called in constructor
    };

} // namespace babel
