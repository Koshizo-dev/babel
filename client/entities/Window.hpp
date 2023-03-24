#pragma once

#include "../ClientManager.hpp"

#include <QWidget>

namespace babel {

    class Window: public QWidget {
        public:
            Window(std::shared_ptr<ClientManager> clientManager);

        private:
            std::shared_ptr<ClientManager> _clientManager;
    };
    
}
