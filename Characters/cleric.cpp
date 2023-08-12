#include "cleric.h"

Cleric::Cleric() : Character(0, 1, 4, 1, 5, 50) { };

void Cleric::useAbility(Character* teammate)
{
    teammate->setLifePoints(teammate->getMaxPS() * 0.5);
}
