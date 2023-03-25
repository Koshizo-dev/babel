#pragma once

#include <exception>
#include <string>

namespace babel {
    class TransporterError : public std::exception {
        public:
            TransporterError(std::string message) : _message(message) {}

            char const *what() const noexcept override {
                if (_message.empty())
                    return ("[TransporterError]: ");
                static std::string _message = ("[TransporterError]: An error occured: " + this->_message);
                return (_message.c_str());
            }

        private:
            std::string const _message;
    };
} // namespace babel
