#pragma once

#include <string>

namespace babel {

    class Message {
        public:
            Message(const std::string sender, const std::string recipient, const std::string content, const std::uint64_t timestamp);

            const std::string getSender() const;
            const std::string getRecipient() const;
            const std::string getContent() const;
            const std::uint64_t getTimestamp() const;

        private:
            const std::string _sender;
            const std::string _recipient;
            const std::string _content;
            const std::uint64_t _timestamp;
    };
    
}