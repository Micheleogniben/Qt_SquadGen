#include "move.h"
#include "character.h"

Move::Move(std::string nm, std::string dsc, unsigned int pDmg, unsigned int mDmg, Type tp):
    name(nm), desc(dsc), phyDmg(pDmg), magDmg(mDmg), type(tp) {}

Move::~Move() = default;

bool Move::isCompatible(const Character* character) const{
    int tp = static_cast<int>(type);
    for (Type t : character->getTypes())
        if (tp == static_cast<int>(t))
            return true;

    return false;
}


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
