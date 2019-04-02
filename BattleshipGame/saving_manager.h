#ifndef SAVING_MANAGER_H
#define SAVING_MANAGER_H

#include <QString>
#include "settings.h"

namespace battleshipGame {

class SavingManager {

    const QString& fileName;

public:
    SavingManager() = delete;
    SavingManager(const QString& fileName);
    void load(Settings&);
    void save(Settings&);
};

}

#endif // SAVING_MANAGER_H
