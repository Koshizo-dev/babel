#pragma once

#include <string>

namespace babel {
    class Message {
        public:
            Message(std::string content, long timestamp, bool isDelivered = false);

            std::string getContent();
            long getTimestamp();

            void setDelivered(bool isDelivered);
            bool isDelivered();
        
        private:
            std::string _content = "";
            long _timestamp = 0;
            bool _isDelivered = false;
    };
}

