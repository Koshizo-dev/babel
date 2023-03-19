#pragma once

#include <string>

namespace babel {

    class DisplaySettings {
        public:
            DisplaySettings(int argc, char **argv, std::string title, int width, int height) : 
                argc(argc), argv(argv), title(title), width(width), height(height) {}

            int argc;
            char **argv;
            std::string title;
            int width;
            int height;
    };

}
