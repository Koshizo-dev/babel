#pragma once

#include "entities/Icon.hpp"
#include <string>

namespace babel {

    class Client {
        public:
            Client(std::string username);

            std::string getUsername();
            std::shared_ptr<Icon> getIcon();
            bool isChatting();
            bool isInCall();
            bool isChatWindow();

            void setChatting(bool isChatting);
            void setInCall(bool isInCall);
            void setChatWindow(bool isChatWindow);

        private:
            std::string _username = "Koshizo";
            std::shared_ptr<Icon> _icon = nullptr;
            bool _isChatting = false;
            bool _isInCall = false;
            bool _isChatWindow = false;

            std::shared_ptr<Icon> _generateIcon(); // Must be called in constructor
    };

} // namespace babel
