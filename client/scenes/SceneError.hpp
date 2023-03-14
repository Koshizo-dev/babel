#pragma once

#include "../ClientError.hpp"

#include <exception>
#include <string>

namespace babel {
    class SceneError : public ClientError {
        public:
            SceneError(std::string message) : ClientError(message), _message(message) {}

            char const *what() const noexcept override {
                static std::string _message = (ClientError::what() + ("[SceneError]: An error occured: " + this->_message));
                return (_message.c_str()); 
            }

        private:
            std::string _message;
    };
} // namespace babel
