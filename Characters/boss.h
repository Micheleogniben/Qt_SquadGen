#ifndef BOSS_H
#define BOSS_H

#include <character.h>

class Boss: public Character
{
public:
    Boss(QString);
    bool useAbility(Character*);
};

#endif // BOSS_H
