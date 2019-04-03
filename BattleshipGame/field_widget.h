#ifndef FIELD_WIDGET_H
#define FIELD_WIDGET_H

#include "battleship_game.h"
#include "widget_painter.h"
#include <QWidget>
#include <memory>

namespace battleshipGame {

class FieldWidget : public QWidget {

    class FieldPainter;

public:
    static const int SIDE;

    FieldWidget();
    QSize sizeHint() const override;
    void paintEvent(QPaintEvent*) override;
};

}

#endif // FIELD_WIDGET_H
