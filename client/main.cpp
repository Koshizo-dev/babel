#include "displays/QDisplay.hpp"
#include <QApplication>
#include <QPushButton>
#include <QFontDatabase>

#include <QtPlugin>

Q_IMPORT_PLUGIN(QXcbIntegrationPlugin);

using namespace babel;

int main(int argc, char **argv) {
    Display *display = new QDisplay(argc, argv, "Babel | New Gen", 1280, 720);

    int code = display->run();

    delete display;
    return (code);
}
