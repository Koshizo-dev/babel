#pragma once

#include "scenes/Scene.hpp"
#include <string>
#include <QApplication>

namespace babel {

class Display {
    public:
        Display(int argc, char **argv, std::string name, int width, int height);
        ~Display();

        int run();

        int centerX(int widgetWidth);
        int centerY(int widgetHeight);

    private:
        void _loadFont();
    
        std::string _name;
        QWidget *_window = nullptr;
        QApplication *_app = nullptr;
        Scene *_currentScene = nullptr;
};

} // namespace babel