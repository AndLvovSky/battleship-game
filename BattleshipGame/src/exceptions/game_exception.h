#ifndef GAME_EXCEPTION_H
#define GAME_EXCEPTION_H

#include <stdexcept>

using namespace std;

namespace battleshipGame {

class GameException : public runtime_error {
public:
    GameException(const char* msg) :
        runtime_error(msg) {}
};

}

#endif // GAME_EXCEPTION_H
