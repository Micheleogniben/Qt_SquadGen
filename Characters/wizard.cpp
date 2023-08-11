#include "wizard.h"

Wizard::Wizard(unsigned short magAtk, unsigned short phyAtk, unsigned short magDef, unsigned short phyDef, unsigned short speed, unsigned short lifePts) :
    Character(magAtk, phyAtk, magDef, phyDef, speed, lifePts) { };

void Wizard::useAbility(Character*)
{

}
