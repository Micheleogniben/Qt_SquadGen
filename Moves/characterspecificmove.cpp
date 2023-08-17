#include "characterspecificmove.h"

CharacterSpecificMove::CharacterSpecificMove(std::string nm, std::string dsc, unsigned int mD, unsigned int pD, Type tp, std::string ch):
    Move(nm, dsc, pD, mD, tp), character(ch) {}
