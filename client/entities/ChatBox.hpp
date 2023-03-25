#pragma once

#include <QWidget>
#include <QTextEdit>
#include <QKeyEvent>

#include "../ClientManager.hpp"

namespace babel {
    class ChatBox: public QWidget {
        public:
            ChatBox(std::string placeHolder, std::shared_ptr<ClientManager> clientManager);

            void handleShiftReturn();
            void handleReturn();

            void setPlaceholderText(std::string placeHolder);

        protected:
            bool eventFilter(QObject* obj, QEvent* event) override;
        
        private:
            std::shared_ptr<ClientManager> _clientManager;
            QTextEdit *_chatInput;
    };

}
