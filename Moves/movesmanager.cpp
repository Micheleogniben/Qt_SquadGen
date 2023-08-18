#include "movesmanager.h"

void MovesManager::addMove(Move* move){
    allMoves.push_back(move);
}

void MovesManager::assignMoves(Character* character) const {
    std::vector<Move*> moves = getCompatibleMoves(character);
    for (Move* m : moves)
        character->addMove(m);
}

std::vector<Move*> MovesManager::getCompatibleMoves(const Character* ch) const {
    std::vector<Move*> moves;
    for (const auto move : allMoves)
        if (move->isCompatible(ch))
            moves.push_back(move);

    return moves;
}
