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

            const std::string getUsername() const;
            Icon *getIcon(int size = 64) const;
            const std::vector<std::shared_ptr<Message>> getMessages() const;
            const bool isChatting() const;
            const bool isInCall() const;
            const bool isChatWindow() const;

            const void addMessage(std::shared_ptr<Message> message);

            const void setChatting(bool isChatting);
            const void setInCall(bool isInCall);
            const void setChatWindow(bool isChatWindow);

        private:
            std::string _username = "Koshizo"; // Easter egg since, not able to have capitals
            bool _isChatting = false;
            bool _isInCall = false;
            bool _isChatWindow = false;
            std::vector<std::shared_ptr<Message>> _messages = {};

            Icon *_generateIcon(int size) const;
    };

} // namespace babel
