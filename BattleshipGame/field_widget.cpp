#include "field_widget.h"
#include "field_painter.h"
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
    FieldPainter(this).paint();
    QWidget::paintEvent(ev);
}
