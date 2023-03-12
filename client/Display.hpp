#pragma once

#include <string>
#include <QApplication>

namespace babel {

class Display {
    public:
        Display(std::string name, int width, int height);
        ~Display();

    private:
        std::string _name;
        QWidget *_window;
};

} // namespace babel