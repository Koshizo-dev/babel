#pragma once

#include "Message.hpp"
#include "entities/Icon.hpp"

#include <string>
#include <mutex>

namespace babel {

    class ClientManager;

    class Client {
        public:
            Client(std::string username);

            std::string getUsername();
            Icon *getIcon(int size = 64);
            std::vector<std::shared_ptr<Message>> getMessages();
            bool isChatting();
            bool isInCall();
            bool isChatWindow();

            void addMessage(std::shared_ptr<Message> message);

            void setChatting(bool isChatting);
            void setInCall(bool isInCall);
            void setChatWindow(bool isChatWindow);

        private:
            std::string _username = "Koshizo"; // Easter egg since, not able to have capitals
            bool _isChatting = false;
            bool _isInCall = false;
            bool _isChatWindow = false;
            std::vector<std::shared_ptr<Message>> _messages = {};
            std::mutex _mutex;

            Icon *_generateIcon(int size);
    };

} // namespace babel
