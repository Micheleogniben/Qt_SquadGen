#ifndef KNIGHT_H
#define KNIGHT_H

#include "character.h"


class Knight : public Character
{
public:
    Knight();
    void useAbility(Character*) override;
};

#endif // KNIGHT_H
