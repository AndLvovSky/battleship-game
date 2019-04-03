#include "field_widget.h"
#include <QPainter>

using namespace battleshipGame;

const int FieldWidget::SIDE = 200;

FieldWidget::FieldWidget() : QWidget() {
    setStyleSheet("border: 2px solid black; background-color: white");
}

QSize FieldWidget::sizeHint() const {
    return QSize(SIDE, SIDE);
}

void FieldWidget::paintEvent(QPaintEvent* ev) {
    QPainter painter(this);
    const auto SQ = SIDE / 10;
    painter.setPen(QColor(100, 100, 100));
    for (int i = 1; i < 10; i++) {
        painter.drawLine(SQ * i, 0, SQ * i, SIDE);
        painter.drawLine(0, SQ * i, SIDE, SQ * i);
    }
    QWidget::paintEvent(ev);
}
