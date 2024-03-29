TEMPLATE = app
TARGET = MyProject


QT += core gui widgets charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

HEADERS += type.h \
    Characters/boss.h \
    gui.h \
    battlemanager.h \
    parser.h \
    squad.h \
    statistics.h

SOURCES += main.cpp \
    Characters/boss.cpp \
    gui.cpp \
    battlemanager.cpp \
    parser.cpp \
    squad.cpp \
    type.cpp \
    statistics.cpp

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
    Moves/movesmanager.h \
    Moves/damagemove.h \
    Moves/statisticmove.h

SOURCES += \
    Moves/move.cpp \
    Moves/movesmanager.cpp \
    Moves/damagemove.cpp \
    Moves/statisticmove.cpp

# Include header and source files from the Gui directory


RESOURCES += \
    resources.qrc

DISTFILES += \
    Resources/knight.png

