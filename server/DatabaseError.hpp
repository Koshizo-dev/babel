
#pragma once

#include <exception>
#include <string>

namespace babel {
    class DatabaseError : public std::exception {
        public:
            DatabaseError(std::string message) : _message(message) {}

            char const *what() const noexcept override {
                if (_message.empty())
                    return ("[DatabaseError]: ");
                static std::string _message = ("[DatabaseError]: An error occured: " + this->_message);
                return (_message.c_str());
            }

        private:
            std::string const _message;
    };
} // namespace babel
