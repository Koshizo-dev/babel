#include "Icon.hpp"

#include <QPainter>
#include <QtCore>

using namespace babel;

Icon::Icon(const std::string &input, QWidget *parent) : QWidget(parent) {
    this->_seed = Icon::_generateSeed(input);
    setFixedSize(64, 64);
}

void Icon::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    const int squareSize = 16;
    const int numSquares = width() / squareSize;
    const int seedSize = this->_seed.size();
    // Define an array of the colors you want to use
    const QColor colors[] = {
        QColor(Qt::red),
        QColor(Qt::green),
        QColor(Qt::blue),
        QColor(Qt::cyan),
        QColor(Qt::black),
        QColor(Qt::gray)
    };
    const int numColors = sizeof(colors) / sizeof(QColor);

    for (int i = 0; i < numSquares; ++i) {
        for (int j = 0; j < numSquares; ++j) {
            // Use the seed value to select a color from the array
            int colorIndex = static_cast<int>(this->_seed[i * numSquares + j % seedSize]) % numColors;
            QColor color = colors[colorIndex];

            painter.setBrush(QBrush(color));
            painter.drawRect(i * squareSize, j * squareSize, squareSize, squareSize);
        }
    }
}

std::string Icon::_generateSeed(const std::string &input)
{
    QCryptographicHash hash(QCryptographicHash::Sha256);
    hash.addData(input.c_str(), input.size());
    QByteArray result = hash.result();
    return result.toHex().toStdString();
}
