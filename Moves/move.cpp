#include "move.h"

Move::Move(std::string nm, std::string dsc, unsigned int mD, unsigned int pD):
    Name(nm), Description(dsc), magicDmg(mD), physicalDmg(pD) {}