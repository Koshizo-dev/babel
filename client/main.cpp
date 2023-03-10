#include <QApplication>
#include <QPushButton>
#include <QFontDatabase>
#include <iostream>

#include <QtPlugin>

Q_IMPORT_PLUGIN(QXcbIntegrationPlugin)

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    QWidget window;
    window.setGeometry(0, 0, 1280, 720);

    // Load the font file
    QFontDatabase::addApplicationFont("assets/Vesta-Pro-Regular.ttf");

    // Set the loaded font as the default font for the application
    QFont font("Vesta-Pro-Regular", 12);
    app.setFont(font);

    QPushButton button("Hello world !", &window);
    button.setGeometry(540, 260, 200, 200);

    int x = (window.width() - button.width()) / 2;
    int y = (window.height() - button.height()) / 2;
    button.move(x, y);

    window.show();

    return app.exec();
}