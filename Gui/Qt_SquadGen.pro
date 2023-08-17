TEMPLATE = app
TARGET = MyProject


QT += core gui widgets charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

HEADERS += type.h \
    Gui/gui.h \
    battlemanager.h \
    squad.h

SOURCES += main.cpp \
    Gui/gui.cpp \
    battlemanager.cpp \
    squad.cpp

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
    Moves/characterspecificmove.h \
    Moves/movesmanager.h

SOURCES += \
    Moves/move.cpp \
    Moves/characterspecificmove.cpp \
    Moves/movesmanager.cpp

# Include header and source files from the Gui directory

INCLUDEPATH += $$PWD/Gui
HEADERS += \

SOURCES += \

RESOURCES += \
    resources.qrc

