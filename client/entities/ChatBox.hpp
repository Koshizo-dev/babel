#pragma once

#include <QWidget>
#include <QTextEdit>
#include <QKeyEvent>

namespace babel {
    class ChatBox: public QWidget {
        public:
            ChatBox(std::string placeHolder);

            void handleShiftReturn();
            void handleReturn();

        protected:
            bool eventFilter(QObject* obj, QEvent* event) override;
        
        private:
            QTextEdit *_chatInput;
    };

}
