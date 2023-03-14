#include "Display.hpp"
#include <QApplication>
#include <QPushButton>
#include <QFontDatabase>

#include <QtPlugin>

Q_IMPORT_PLUGIN(QXcbIntegrationPlugin);

int main(int argc, char **argv) {

    babel::Display display(argc, argv, "Sample title", 1280, 720);

    return display.run();
}