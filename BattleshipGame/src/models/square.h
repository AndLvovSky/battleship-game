#ifndef SQUARE_H
#define SQUARE_H

namespace battleshipGame {

class Square {

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
    int getX() const;
    void setX(int);
    int getY() const;
    void setY(int);
    bool operator == (const Square&) const;
    bool operator != (const Square&) const;
    Square& operator=(const Square&);
};

}

#endif // SQUARE_H
