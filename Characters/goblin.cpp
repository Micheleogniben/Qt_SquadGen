#include "goblin.h"
#include <cmath>


Goblin::Goblin() : Character(0, 4, 0, 2, 9, 0, 15, {}, CharType::Goblin) { };

// L'abilità dei goblin consiste nell'aumentare del 10% ad ogni turno l'attacco, sia magico che fisico
bool Goblin::useAbility(Character*){
    setPhyAtk(getPhyAtk() * 0.1 + getPhyAtk());
    setMagAtk(getMagAtk() * 0.1 + getMagAtk());
    setAbilityUsed(true);
    return true;
}

// la funzione std::ceil arrotonda per eccesso i numeri con parte frazionaria maggiore di 0, in questo modo
// aggiungo nu goblin se il risultato è decimale, perché questo significherebbe che ho un goblin in più con poca vita
void Goblin::setLifePoints(const unsigned short lifePts){
    Character::setLifePoints(lifePts);
    setAmount(std::ceil(lifePts / getMaxPS()));
}

unsigned short Goblin::getAmount() const{
    return amount;
}

void Goblin::setAmount(unsigned short newValue){
    amount = newValue < 0 ? 0 : newValue > 5 ? 5 : newValue;
}
