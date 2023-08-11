#include "characterspecificmove.h"

CharacterSpecificMove::CharacterSpecificMove(std::string nm, std::string dsc, unsigned int mD, unsigned int pD, std::string ch):
    Move(nm,dsc,mD,pD), Character(ch) {}

CharacterSpecificMove::~CharacterSpecificMove(){
    delete this;
}
