#include "goblin.h"

Goblin::Goblin(unsigned short magAtk, unsigned short phyAtk, unsigned short magDef, unsigned short phyDef, unsigned short speed, unsigned short lifePts) :
    Character(magAtk, phyAtk, magDef, phyDef, speed, lifePts) { };

void Goblin::useAbility(Character*)
{

}

unsigned short Goblin::getAmount()
{
    return amount;
}

void Goblin::setAmount(unsigned short newValue)
{
    amount = newValue;
}
