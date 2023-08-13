#ifndef CLERIC_H
#define CLERIC_H

#include "character.h"


class Cleric : public Character
{
public:
    Cleric();
    bool useAbility(Character*) override;
};

#endif // CLERIC_H
