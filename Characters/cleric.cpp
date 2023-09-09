#include "cleric.h"
#include "statistics.h"

Cleric::Cleric(QString n) : Character(clericStats, n) { };

Cleric::Cleric(const Cleric& other) : Character(other) { };

bool Cleric::useAbility(Character* teammate){
    if (getAbilityUsed())
        return false;

    teammate->setLifePoints(teammate->getMaxPS() * 2);
    setAbilityUsed(true);
    return true;
}
