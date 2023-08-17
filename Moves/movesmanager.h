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

    void addMove(const Move&);
    void assingMoves(Character&);
    //const std::vector<const CharacterSpecificMove* const> getCharacterMoves(std::string) const;
};

#endif // MOVESMANAGER_H
