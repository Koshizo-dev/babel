#pragma once

#include <exception>
#include <string>

namespace babel {
    class ClientError : public std::exception {
        public:
            ClientError(std::string message) : _message(message) {}
            ClientError() {}

            char const *what() const noexcept override {
                if (_message.empty())
                    return ("[ClientError]: ");
                static std::string _message = ("[ClientError]: An error occured: " + this->_message);
                return (_message.c_str());
            }

        private:
            std::string const _message;
    };
} // namespace babel
