#ifndef SETTINGS_H
#define SETTINGS_H

#include <map>

using namespace std;

namespace battleshipGame {

class Settings {

    map<int, int> decksToNumber;
    bool timeLimited;
    int stepDuration;

    Settings() = default;

public:
    static const int
        MIN_DECKS,
        MAX_DECKS,
        MIN_STEP_DURATION,
        MAX_STEP_DURATION;
   static const map<int, int>
        MIN_DECKS_NUMBER,
        MAX_DECKS_NUMBER;

    void setShipsMap(const map<int, int>&);
    map<int, int> getShipsMap();
    void setTimeLimited(bool);
    bool isTimeLimited();
    void setStepDuration(int);
    int getStepDuration();
    static Settings& getInstance();
    Settings& operator=(Settings&) = delete;
    Settings& operator=(Settings&&) = delete;
};

}

#endif // SETTINGS_H
