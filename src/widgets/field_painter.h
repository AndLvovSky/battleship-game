#ifndef FIELD_PAINTER_H
#define FIELD_PAINTER_H

#include "field_widget.h"
#include "widget_painter.h"
#include "../models/ship.h"

using namespace std;

namespace battleshipGame {

class FieldWidget::FieldPainter : public WidgetPainter<FieldWidget> {

    const int SQ = SIDE / 10;
    const bool yours;
    const QColor FIELD_COLOR = QColor(80, 80, 80);
    const QColor CORRECT_COLOR = QColor(255, 255, 0);
    const QColor INCORRECT_COLOR = QColor(255, 0, 0, 100);
    const QColor SHIP_COLOR = QColor(0, 0, 255);
    const QColor ATTACK_COLOR = QColor(255, 0, 0);
    const int NARROW_STROKE = 2;
    const int THICK_STROKE = 4;

    void drawField();
    void drawFleet();
    void drawFleetState();
    void drawShip(Ship ship, QColor color);
    void drawSquare(Square square, QColor color);
    void drawCross(Square);
    void drawSmallPoint(Square);
    QPoint point(Square);
    void drawPlacing();
    void drawBattle();

public:
    FieldPainter(FieldWidget* fw);
    void paint() override;
};

}

#endif // FIELD_PAINTER_H
