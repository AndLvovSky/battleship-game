#-------------------------------------------------
#
# Project created by QtCreator 2019-04-02T09:18:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BattleshipGame
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++17

SOURCES += \
        main.cpp \
    settings.cpp \
    saving_manager.cpp \
    field_widget.cpp \
    square.cpp \
    ship.cpp \
    fleet.cpp \
    widget_painter.cpp \
    field_painter.cpp \
    battleship_game.cpp \
    main_window.cpp

HEADERS += \
    settings.h \
    saving_manager.h \
    game_exception.h \
    field_widget.h \
    square.h \
    ship.h \
    fleet.h \
    shot.h \
    widget_painter.h \
    field_painter.h \
    battleship_game.h \
    main_window.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc

DISTFILES += \
    ../build-BattleshipGame-Desktop_Qt_5_12_2_MinGW_32_bit-Debug/debug/BattleshipGame.exe \
    ../build-BattleshipGame-Desktop_Qt_5_12_2_MinGW_32_bit-Debug/settings.txt
