#pragma once

#include "entities/Icon.hpp"
#include <string>

namespace babel {

    class Client {
        public:
            Client(std::string username);

            std::string getUsername();
            std::shared_ptr<Icon> getIcon();

        private:
            std::string _username;
            std::shared_ptr<Icon> _icon;

            std::shared_ptr<Icon> _generateIcon(); // Must be called in constructor
    };

} // namespace babel
