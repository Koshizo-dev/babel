#pragma once

namespace babel {

class Display {
    public:
        virtual ~Display() {}
    
        virtual int run() = 0;
};

} // namespace babel