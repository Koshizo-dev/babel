#include "ChatBox.hpp"
#include <QScrollBar>

using namespace babel;

ChatBox::ChatBox(std::string placeHolder) {
    this->_chatInput = new QTextEdit(this);
    // this->_chatInput->setLineWrapColumnOrWidth(300);
    
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->_chatInput->setPlaceholderText(placeHolder.c_str());

    this->_chatInput->installEventFilter(this);
}

bool ChatBox::eventFilter(QObject *object, QEvent *event) {
    if (object != this->_chatInput)
        return (QWidget::eventFilter(object, event));

    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        Qt::KeyboardModifiers modifiers = keyEvent->modifiers();
        if (keyEvent->key() == Qt::Key_Return && modifiers == Qt::ShiftModifier) {
            this->handleShiftReturn();
            return true;
        }
    }
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_Return) {
            this->handleReturn();
            return true;
        }
    }

    return (QWidget::eventFilter(object, event));
}

void ChatBox::handleShiftReturn() {
    QFontMetrics fontMetrics(this->_chatInput->font());
    int lineHeight = fontMetrics.lineSpacing();

    this->_chatInput->ensureCursorVisible();
    //else
    //    this->_chatInput->verticalScrollBar()->setValue(scrollbarPrevValue - lineHeight);
    this->_chatInput->insertPlainText("\n"); // Append a new line
    printf("Shift + Return key press detected.\n");
}

void ChatBox::handleReturn() {
    printf("Return key press detected.\n");
}
