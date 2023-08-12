#include "dragon.h"
#include "goblin.h"

Dragon::Dragon() : Character(8, 8, 3, 8, 2, 100) { };

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
