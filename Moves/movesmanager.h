#ifndef MOVESMANAGER_H
#define MOVESMANAGER_H

#include <damagemove.h>
#include <statisticmove.h>
#include "character.h"

#include <vector>

class MovesManager
{
public:
    MovesManager();
    void addMove(Move*);
    std::vector<Move*> getCompatibleMoves(const Character*) const;
    Move* moveByName(QString) const;

    static std::vector<Move*> allMoves;
};

#endif // MOVESMANAGER_H
