TEMPLATE = app
TARGET = MyProject

SOURCES += main.cpp \
    Moves/characterspecificmove.cpp \
    Moves/movesmanager.cpp \
    Moves/typespecificmove.cpp \
    main.cpp

# Include header and source files from the Characters directory
INCLUDEPATH += $$PWD/Characters
HEADERS += \
    Characters/character.h \
    Characters/cleric.h \
    Characters/dragon.h \
    Characters/goblin.h \
    Characters/knight.h \
    Characters/wizard.h \
    Moves/characterspecificmove.h \
    Moves/movesmanager.h \
    Moves/typespecificmove.h

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
    Moves/move.h

SOURCES += \
    Moves/move.cpp
