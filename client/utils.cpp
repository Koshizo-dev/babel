#include "utils.hpp"

int babel::centerX(QWidget *parent, int widgetWidth) {
    return ((parent->width() - widgetWidth) / 2);
}

int babel::centerY(QWidget *parent, int widgetHeight) {
    return ((parent->height() - widgetHeight) / 2);
}
