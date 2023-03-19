#pragma once

#include <QHBoxLayout>
#include <QMouseEvent>
#include <QObject>

namespace babel {
    class ClickableHBoxLayout : public QHBoxLayout {
        Q_OBJECT

        public:
            ClickableHBoxLayout(QWidget *parent = nullptr);

        signals:
            void clicked();

        protected:
            void mousePressEvent(QMouseEvent *event);
    };
}