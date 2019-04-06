#ifndef FIELD_WIDGET_H
#define FIELD_WIDGET_H

#include "battleship_game.h"
#include "widget_painter.h"
#include <QLabel>
#include <memory>

namespace battleshipGame {

class FieldWidget : public QWidget {

    Q_OBJECT

    class FieldPainter;

    const bool yours;

    Square getSquare(int wx, int wy);

public:
    static const int SIDE;

    FieldWidget(bool yours);
    virtual ~FieldWidget() override;
    QSize sizeHint() const override;
    void paintEvent(QPaintEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void mousePressEvent(QMouseEvent*) override;
    void enterEvent(QEvent*) override;
    void leaveEvent(QEvent*) override;
    //bool eventFilter(QObject*, QEvent*) override;

signals:
    void shipsMapChanged();
    void fired(Shot);
};

}

#endif // FIELD_WIDGET_H
