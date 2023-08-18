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
    void addMove(Move*);
    void assignMoves(Character*) const;
    std::vector<Move*> getCompatibleMoves(const Character*) const;
};

#endif // MOVESMANAGER_H
