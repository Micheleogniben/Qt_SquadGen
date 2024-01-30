#include "dragon.h"
#include <cstdlib>
#include <ctime>

Dragon::Dragon(QString n) : Character(dragonStats, n) { };

Dragon::Dragon(const Dragon& other) : Character(other) { };

bool Dragon::useAbility(Character* target){
    if (getAbilityUsed())
        return false;

    std::srand(static_cast<unsigned int>(std::time(0)));
    target->setLifePoints(target->getLifePoints() * 0.7);

    target->setBurning((std::rand() % 4) + 3);

    setAbilityUsed(true);
    return true;
}
