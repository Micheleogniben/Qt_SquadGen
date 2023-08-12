#include "knight.h"

Knight::Knight() : Character(0, 10, 0, 10, 4, 90) { };

// L'abilità del cavaliere onsiste in un attacco che sarà inversamente proporzionale alla sua vita: minore sarà la sua vita,
// quindi maggiore sarà il danno inflitto all'avversario. Abbiamo pensato ad un danno massimo di 50 ed un danno minimo di 0
void Knight::useAbility(Character* enemy)
{
    unsigned short myLifePts = getLifePoints();
    unsigned short damage = ((90 - myLifePts) / 90) * 50;
    enemy->setLifePoints(enemy->getLifePoints() - damage);
}
