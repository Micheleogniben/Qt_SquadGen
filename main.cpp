#include <QApplication>
#include <QWidget>
#include "startScreen.h"
#include "dragon.h"
#include "knight.h"
#include "wizard.h"
#include "movesmanager.h"
#include "characterspecificmove.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QWidget window;

    // Creazione delle mosse
    MovesManager movesManager;

    movesManager.addMove(new Move("Fireball", "A ball of fire that burns the target", 3, 20, Type::Fire));
    movesManager.addMove(new Move("Whirlwind", "Whips up a cyclone to damage the enemy", 10, 19, Type::Air));
    movesManager.addMove(new Move("Kick", "Delivers a kick to the target", 24, 5, Type::Neutral));
    movesManager.addMove(new CharacterSpecificMove("Sonic Boom", "Emits a shockwave that damages the target", 0, 14, Type::Poison, CharType::Wizard));
    // ... altre mosse ...

    // Creazione dei personaggi
    Dragon dragon;
    Knight knight;
    Wizard wizard;
    // ... altri personaggi ...

    // Assegnazione delle mosse ai personaggi tramite MovesManager
    movesManager.assignMoves(&dragon);
    movesManager.assignMoves(&knight);
    movesManager.assignMoves(&wizard);

    startScreen(&window);
    return app.exec();
}
