#ifndef GOBLIN_H
#define GOBLIN_H

#include "character.h"


class Goblin : public Character
{
private:
    unsigned short amount;
public:
    Goblin(QString);
    bool useAbility(Character*) override;
    void setLifePoints(const unsigned short) override;

    unsigned short getAmount() const;
    void setAmount(unsigned short);
};

#endif // GOBLIN_H
