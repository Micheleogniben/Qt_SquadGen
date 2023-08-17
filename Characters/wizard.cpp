#include "wizard.h"

Wizard::Wizard() : Character(10, 3, 10, 5, 7, 75) { };

// L'abilità dello stregone consiste nel ridurre del 30% ogni statistica dell'avversario (esclusa la vita)
bool Wizard::useAbility(Character* enemy){
    if (getAbilityUsed())
        return false;

    enemy->setMagAtk(enemy->getMagAtk() * 0.7);
    enemy->setPhyAtk(enemy->getPhyAtk() * 0.7);
    enemy->setMagDef(enemy->getMagDef() * 0.7);
    enemy->setPhyDef(enemy->getPhyDef() * 0.7);
    enemy->setSpeed(enemy->getSpeed() * 0.7);
    setAbilityUsed(true);
    return true;
}
