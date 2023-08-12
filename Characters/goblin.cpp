#include "goblin.h"
#include <cmath>


Goblin::Goblin() : Character(0, 4, 0, 2, 9, 15) { };

void Goblin::useAbility(Character*)
{

}

// la funzione std::ceil arrotonda per eccesso i numeri con parte frazionaria maggiore di 0, in questo modo
// aggiungo nu goblin se il risultato è decimale, perché questo significherebbe che ho un goblin in più con poca vita
void Goblin::setLifePoints(const unsigned short lifePts)
{
    Character::setLifePoints(lifePts);
    setAmount(std::ceil(lifePts / 15));
}

unsigned short Goblin::getAmount() const
{
    return amount;
}

void Goblin::setAmount(unsigned short newValue)
{
    amount = newValue;
}
