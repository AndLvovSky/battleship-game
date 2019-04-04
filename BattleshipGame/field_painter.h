#ifndef FIELD_PAINTER_H
#define FIELD_PAINTER_H

#include "field_widget.h"
#include "widget_painter.h"
#include "ship.h"
#include "battleship_game.h"

using namespace std;

namespace battleshipGame {

class FieldWidget::FieldPainter : public WidgetPainter<FieldWidget> {

    const int SQ = SIDE / 10;

    void drawFrame(int startX, int startY, int finalX, int finalY,
                   int color, int width);
    void drawField(int x, int y, string name);
    void drawFleetsFields();
    void drawShip(Ship ship, int fieldX, int fieldY);
    void drawPoint(int fieldX, int fieldY);
    void drawCross(int fieldX, int fieldY);
    void drawFleetState(bool isYour, int fieldX, int fieldY);
    void drawYourFleetState();
    void drawOpponentFleetState();
    void highlightSquare(Square square);
    void drawPlacing();
    void drawBattle();
    QPoint point(Square);

public:
    FieldPainter(FieldWidget* fw);
    void paint() override;
};

}

#endif // FIELD_PAINTER_H
