#include "field_widget.h"
#include "field_painter.h"
#include <QPainter>
#include <QMouseEvent>
#include <QStyleOption>

using namespace battleshipGame;

FieldWidget::FieldWidget(bool yours, QWidget& parent) :
    QWidget(), yours(yours), parent(parent) {
    setStyleSheet("border: 2px solid black; background-color: white");
    this->setMouseTracking(true);
}

FieldWidget::~FieldWidget() {}

void FieldWidget::paintEvent(QPaintEvent* ev) {
    //<required>
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    //</required>
    int h = parent.height();
    side = h * 2 / 5 / 10 * 10;
    this->setFixedSize(QSize(side, side));
    FieldPainter(this, side).paint();
    QWidget::paintEvent(ev);
}

void FieldWidget::mouseMoveEvent(QMouseEvent* ev) {
    auto& game = BattleshipGame::get();
    if (game.mode == BattleshipGame::Mode::PLACING && !yours ||
        game.mode == BattleshipGame::Mode::BATTLE && yours) {
        return;
    }
    if (ev->type() == QEvent::MouseMove) {
       Square square = getSquare(ev->x(), ev->y());
       if (game.square != square) {
           game.square = square;
           update();
       }
    }
}

void FieldWidget::mousePressEvent(QMouseEvent *ev) {
    auto& game = BattleshipGame::get();
    if (game.mode == BattleshipGame::Mode::PLACING && !yours ||
        game.mode == BattleshipGame::Mode::BATTLE && yours && game.stepYours) {
        return;
    }
    if (ev->buttons() & Qt::RightButton) {
        QMessageLogger().debug("right button clicked");
        if (game.mode == BattleshipGame::Mode::PLACING) {
            game.shipHorizontal = !game.shipHorizontal;
            update();
        }
    } else if (ev->buttons() & Qt::LeftButton) {
        QMessageLogger().debug("left button clicked");
        if (game.mode == BattleshipGame::Mode::PLACING) {
            auto& yourFleet = game.getFleet(true);
            Ship ship(game.square, game.shipSize, game.shipHorizontal);
            if (game.shipsLeft[game.shipSize] &&
                yourFleet.checkPositionForShip(ship)) {
                yourFleet.addShip(ship);
                game.shipsLeft[game.shipSize]--;
                emit shipsMapChanged();
            }
        } else if (game.mode == BattleshipGame::Mode::BATTLE && game.stepYours) {
            auto& opponentFleet = game.getFleet(false);
            if (!opponentFleet.hasAttacked(game.square)) {
                FireResult result = opponentFleet.fire(game.square);
                QMessageLogger().debug("you fired");
                update();
                emit fired(result);
            }
        }
    }
}

void FieldWidget::enterEvent(QEvent* ev) {
    QMessageLogger().debug("enter");
    BattleshipGame::get().squareSelected = true;
    QWidget::enterEvent(ev);
}

void FieldWidget::leaveEvent(QEvent* ev) {
    QMessageLogger().debug("leave");
    BattleshipGame::get().squareSelected = false;
    update();
    QWidget::leaveEvent(ev);
}

Square FieldWidget::getSquare(int wx, int wy) {
    return {wx * 10 / side, wy * 10 / side};
}
