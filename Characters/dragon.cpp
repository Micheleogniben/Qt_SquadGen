#include "dragon.h"
#include "goblin.h"

Dragon::Dragon(unsigned short magAtk, unsigned short phyAtk, unsigned short magDef, unsigned short phyDef, unsigned short speed, unsigned short lifePts) :
    Character(magAtk, phyAtk, magDef, phyDef, speed, lifePts) { };

void Dragon::useAbility(Character* target)
{
    if (dynamic_cast<Goblin*>(target))
    {
        Goblin* goblinTarget = static_cast<Goblin*>(target);
        //tolgo 200 punti vita per ogni goblin che viene schierato
        goblinTarget->setLifePoints((goblinTarget->getLifePoints() - 200) * goblinTarget->getAmount());
        // ipotizzando 400 punti vita per ciascun goblin, dopo aver aggiornato i punti vita per l'attacco subito, aggiorno anche
        // la quantità che forma l'orda di goblin che ora è probabilmente diminuita per colpa dell'attacco del drago
        goblinTarget->setAmount(goblinTarget->getLifePoints() / 400);
    }
}
