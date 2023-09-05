#ifndef MOVESMANAGER_H
#define MOVESMANAGER_H

#include <damagemove.h>
#include <statisticmove.h>
#include "character.h"

#include <vector>

class MovesManager
{
private:
    std::vector<Move*> allMoves;

public:
    MovesManager();
    void addMove(Move*);
    std::vector<Move*> getCompatibleMoves(const Character*) const;
    Move* moveByName(QString) const;
};

#endif // MOVESMANAGER_H
