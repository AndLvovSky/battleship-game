#ifndef SQUARE_H
#define SQUARE_H

namespace battleshipGame {

class Square {

    private:

    int x, y;

    public:

    enum State {
        NOT_ATTACKED,
        ATTACKED,
        ATTACKED_WITH_SUCCESS
    };

    Square();
    Square(int, int);
    static Square makeSquare(int, int);
    int getX();
    void setX(int);
    int getY();
    void setY(int);
    bool operator == (Square);
};

}

#endif // SQUARE_H
