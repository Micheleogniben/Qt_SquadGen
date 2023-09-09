#include "boss.h"

Boss::Boss(QString n) : Character(bossStats,n) { };

bool Boss::useAbility(Character* target){
    if(getAbilityUsed()) return false;
    target->setPhyAtk(3);
    setAbilityUsed(true);
    return true;
}
