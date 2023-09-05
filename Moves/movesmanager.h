#ifndef MOVESMANAGER_H
#define MOVESMANAGER_H

#include "move.h"
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
};

#endif // MOVESMANAGER_H
