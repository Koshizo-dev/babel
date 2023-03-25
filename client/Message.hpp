#pragma once

#include <memory>
#include <string>

namespace babel {

    class Client;

    class Message {
        public:
            Message(std::shared_ptr<Client> author, std::string content, long timestamp, bool isDelivered = false);

            const std::shared_ptr<Client> getAuthor() const;
            const std::string getContent() const;
            const long getTimestamp() const;
            const bool isDelivered() const;

            const void setDelivered(bool isDelivered);

        private:
            std::shared_ptr<Client> _author = nullptr;
            std::string _content = "";
            long _timestamp = 0;
            bool _isDelivered = false;
    };
}

