#include "character.h"

// CONSTRUCTORS
Character::Character() { };

Character::Character(unsigned short magAtk, unsigned short phyAtk, unsigned short magDef, unsigned short phyDef, unsigned short speed, unsigned short lifePts) :
    stats{magAtk, phyAtk, magDef, phyDef, speed, lifePts} { };

// GET METHODS
unsigned short Character::getPhyAtk()
{
    return stats.physicalAtk;
}

unsigned short Character::getMagAtk()
{
    return stats.magicAtk;
}

unsigned short Character::getPhyDef()
{
    return stats.physicalDef;
}

unsigned short Character::getMagDef()
{
    return stats.magicDef;
}

unsigned short Character::getLifePoints()
{
    return stats.lifePoints;
}

// SET METHODS
void Character::setPhyAtk(unsigned short amount)
{
    stats.physicalAtk = amount < 0 ? 0 : amount > 10 ? 10 : amount;
}

void Character::setMagAtk(unsigned short amount)
{
    stats.magicAtk = amount < 0 ? 0 : amount > 10 ? 10 : amount;
}

void Character::setMagDef(unsigned short amount)
{
    stats.magicDef = amount < 0 ? 0 : amount > 10 ? 10 : amount;
}

void Character::setPhyDef(unsigned short amount)
{
    stats.physicalDef = amount < 0 ? 0 : amount > 10 ? 10 : amount;
}

void Character::setLifePoints(unsigned short amount)
{
    stats.lifePoints = amount < 0 ? 0 : amount > 10 ? 10 : amount;
}
