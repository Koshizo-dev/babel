#pragma once

#include <string>

namespace babel {
    class Message {
        public:
            Message(std::string content, long timestamp);

        private:
            std::string _content;
            long _timestamp;
    };
}

