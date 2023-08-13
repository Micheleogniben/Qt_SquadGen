#include "character.h"

// CONSTRUCTORS
Character::Character(unsigned short magAtk, unsigned short phyAtk, unsigned short magDef, unsigned short phyDef, unsigned short speed, unsigned short lifePts) :
    maxPS(lifePts), abilityUsed(false), stats{magAtk, phyAtk, magDef, phyDef, speed, lifePts} { };

// GET METHODS
unsigned short Character::getPhyAtk() const
{
    return stats.physicalAtk;
}

unsigned short Character::getMagAtk() const
{
    return stats.magicAtk;
}

unsigned short Character::getPhyDef() const
{
    return stats.physicalDef;
}

unsigned short Character::getMagDef() const
{
    return stats.magicDef;
}

unsigned short Character::getSpeed() const
{
    return stats.speed;
}

unsigned short Character::getLifePoints() const
{
    return stats.lifePoints;
}

unsigned short Character::getMaxPS() const
{
    return maxPS;
}

bool Character::getAbilityUsed() const
{
    return abilityUsed;
}

// SET METHODS
void Character::setPhyAtk(const unsigned short amount)
{
    stats.physicalAtk = amount < 0 ? 0 : amount > 10 ? 10 : amount;
}

void Character::setMagAtk(const unsigned short amount)
{
    stats.magicAtk = amount < 0 ? 0 : amount > 10 ? 10 : amount;
}

void Character::setMagDef(const unsigned short amount)
{
    stats.magicDef = amount < 0 ? 0 : amount > 10 ? 10 : amount;
}

void Character::setPhyDef(const unsigned short amount)
{
    stats.physicalDef = amount < 0 ? 0 : amount > 10 ? 10 : amount;
}

void Character::setSpeed(const unsigned short amount)
{
    stats.speed = amount < 0 ? 0 : amount > 10 ? 10 : amount;
}

void Character::setAbilityUsed(const bool val)
{
    abilityUsed = val;
}

void Character::setLifePoints(const unsigned short amount)
{
    stats.lifePoints = amount < 0 ? 0 : amount > maxPS ? maxPS : amount;
}
