#ifndef MOVESMANAGER_H
#define MOVESMANAGER_H

#include <characterspecificmove.h>
#include <typespecificmove.h>

#include <vector>

class MovesManager
{
private:
    std::vector<Move*> AvailableMoves;
public:
    MovesManager();
    void addMove();
    void removeMove(std::string);
    const std::vector<const Move* const> getAllMoves();
    const std::vector<const TypeSpecificMove* const> getTypeMoves(std::string);
    const std::vector<const CharacterSpecificMove* const> getCharacterMoves(std::string);
    Move& modifyMove(std::string);

};

#endif // MOVESMANAGER_H
