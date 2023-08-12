#ifndef DRAGON_H
#define DRAGON_H

#include "character.h"


class Dragon : public Character
{
public:
    Dragon();
    void useAbility(Character*) override;
};

#endif // DRAGON_H
