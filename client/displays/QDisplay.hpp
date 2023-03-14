#pragma once

#include "Display.hpp"

#include <string>
#include <QApplication>
#include "../scenes/Scene.hpp"

namespace babel {
    class QDisplay : public Display {
        public:
            QDisplay(int argc, char **argv, std::string name, int width, int height);
            ~QDisplay();
            
            int run() override;
    private:
        void _loadFont();
    
        std::string _name;
        QWidget *_window = nullptr;
        QApplication *_app = nullptr;
        Scene *_currentScene = nullptr;
    };
} // namespace babel
