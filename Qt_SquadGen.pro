TEMPLATE = app
TARGET = MyProject


QT += core gui widgets charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

HEADERS += type.h \
    Moves/damagemove.h \
    Moves/statisticmove.h \
    controller.h \
    gui.h \
    battlemanager.h \
    squad.h \
    statistics.h

SOURCES += main.cpp \
    Moves/damagemove.cpp \
    Moves/statisticmove.cpp \
    controller.cpp \
    gui.cpp \
    battlemanager.cpp \
    squad.cpp \
    statistics.cpp \
    type.cpp

# Include header and source files from the Characters directory
INCLUDEPATH += $$PWD/Characters
HEADERS += \
    Characters/character.h \
    Characters/cleric.h \
    Characters/dragon.h \
    Characters/goblin.h \
    Characters/knight.h \
    Characters/wizard.h \

SOURCES += \
    Characters/character.cpp \
    Characters/cleric.cpp \
    Characters/dragon.cpp \
    Characters/goblin.cpp \
    Characters/knight.cpp \
    Characters/wizard.cpp

# Include header and source files from the Moves directory
INCLUDEPATH += $$PWD/Moves
HEADERS += \
    Moves/move.h \
    Moves/movesmanager.h

SOURCES += \
    Moves/move.cpp \
    Moves/movesmanager.cpp

# Include header and source files from the Gui directory


RESOURCES += \
    resources.qrc

DISTFILES += \
    Resources/knight.png

