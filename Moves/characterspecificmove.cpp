#include "characterspecificmove.h"
#include "character.h"


CharacterSpecificMove::CharacterSpecificMove(std::string nm, std::string dsc, unsigned int mD, unsigned int pD, Type tp, CharType cTp):
    Move(nm, dsc, pD, mD, tp), charType(cTp) {}

CharacterSpecificMove::~CharacterSpecificMove() = default;

bool CharacterSpecificMove::isCompatible(const Character* c) const{
    if (Move::isCompatible(c))
        return true;

    return charType == c->getCharType();
}
