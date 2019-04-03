#ifndef FIELD_WIDGET_H
#define FIELD_WIDGET_H

#include <QWidget>

namespace battleshipGame {

class FieldWidget : public QWidget {

    static const int SIDE;

public:
    FieldWidget();
    QSize sizeHint() const override;
    void paintEvent(QPaintEvent*) override;
};

}

#endif // FIELD_WIDGET_H
