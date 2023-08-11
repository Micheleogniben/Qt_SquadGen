#ifndef GOBLIN_H
#define GOBLIN_H

#include "character.h"


class Goblin : public Character
{
private:
    unsigned short amount;
public:
    Goblin(unsigned short, unsigned short, unsigned short, unsigned short, unsigned short, unsigned short);
    void useAbility(Character*) override;

    unsigned short getAmount();
    void setAmount(unsigned short);
};

#endif // GOBLIN_H
