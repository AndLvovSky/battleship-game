#ifndef SAVING_MANAGER_H
#define SAVING_MANAGER_H

#include <QString>
#include <QFile>
#include "settings.h"

namespace battleshipGame {

class SavingManager {

    QFile sfile;

public:
    SavingManager() = delete;
    SavingManager(const QString& fileName);
    void load(Settings&);
    void save(Settings&);
};

}

#endif // SAVING_MANAGER_H
