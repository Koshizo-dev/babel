#pragma once

#include <string>

namespace babel {
    class Database {
        public:
            virtual void connect() = 0;
            virtual void disconnect() = 0;
            virtual void init() = 0;
    };
}
