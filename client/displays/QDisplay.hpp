#pragma once

#include "Display.hpp"

#include <string>
#include <QApplication>
#include "../scenes/Scene.hpp"
#include "../scenes/SceneManager.hpp"

namespace babel {
    class QDisplay : public Display {
        public:
            QDisplay(int argc, char **argv, std::string name, int width, int height);
            ~QDisplay();
            
            int run() override;
    private:
        void _loadFont();
    
        std::string _name;
        std::shared_ptr<QWidget> _window = nullptr;
        std::unique_ptr<QApplication> _app = nullptr;
        std::shared_ptr<SceneManager> _sceneManager = nullptr;
    };
} // namespace babel
