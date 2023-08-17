#include "cleric.h"

Cleric::Cleric() : Character(0, 1, 4, 1, 5, 50) { };

bool Cleric::useAbility(Character* teammate){
    if (getAbilityUsed())
        return false;

    if (teammate->getLifePoints())
        return false;

    teammate->setLifePoints(teammate->getMaxPS() * 0.5);
    setAbilityUsed(true);
    return true;
}
