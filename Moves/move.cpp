#include "move.h"

Move::Move(std::string nm, std::string dsc, unsigned int pDmg, unsigned int mDmg, Type tp):
    name(nm), desc(dsc), phyDmg(pDmg), magDmg(mDmg), type(tp) {}

std::string Move::getName() const{
    return name;
}

std::string Move::getDescription() const{
    return desc;
}

unsigned int Move::getPhyDamage() const{
    return phyDmg;
}

unsigned int Move::getMagDamage() const{
    return magDmg;
}

Type Move::getType() const{
    return type;
}
