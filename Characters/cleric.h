#ifndef CLERIC_H
#define CLERIC_H

#include "character.h"


class Cleric : public Character
{
public:
    Cleric(unsigned short, unsigned short, unsigned short, unsigned short, unsigned short, unsigned short);
    void useAbility(Character*) override;
};

#endif // CLERIC_H
