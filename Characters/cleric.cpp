#include "cleric.h"

Cleric::Cleric(unsigned short magAtk, unsigned short phyAtk, unsigned short magDef, unsigned short phyDef, unsigned short speed, unsigned short lifePts) :
    Character(magAtk, phyAtk, magDef, phyDef, speed, lifePts) { };

void Cleric::useAbility(Character* target)
{
    target->setLifePoints(target->getLifePoints() + target->getLifePoints() * 0.20);
}
