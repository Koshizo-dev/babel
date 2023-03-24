#pragma once

#include "Display.hpp"

#include "../scenes/Scene.hpp"
#include "../ClientManager.hpp"
#include "DisplaySettings.hpp"

#include <string>
#include <QApplication>

namespace babel {
    class QDisplay : public Display {
        public:
            QDisplay(DisplaySettings settings, std::shared_ptr<ClientManager> clientManager);
            ~QDisplay();
            
            int run() override;
    private:
        void _loadFont();

        DisplaySettings _settings;
        std::unique_ptr<QWidget> _window = nullptr;
        std::unique_ptr<QApplication> _app = nullptr;
        std::shared_ptr<ClientManager> _clientManager = nullptr;
    };
} // namespace babel
