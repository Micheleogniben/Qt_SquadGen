#include "dragon.h"
#include <cstdlib>
#include <ctime>

Dragon::Dragon(QString n) : Character(dragonStats,n) { };

bool Dragon::useAbility(Character* target){
    if (getAbilityUsed())
        return false;

    std::srand(static_cast<unsigned int>(std::time(0)));
    target->setLifePoints(target->getLifePoints() * 0.7);

    target->setBurning((arc4random() % 4) + 3);

    setAbilityUsed(true);
    return true;
}
