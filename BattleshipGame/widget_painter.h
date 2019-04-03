#ifndef WIDGET_PAINTER_H
#define WIDGET_PAINTER_H

#include <QWidget>
#include <QPainter>

template <typename QWidgetType>
class WidgetPainter {

protected:
    QPainter* painter;

public:
    WidgetPainter(QWidget*);
    virtual ~WidgetPainter();
    virtual void paint() = 0;
};

#endif // WIDGET_PAINTER_H
