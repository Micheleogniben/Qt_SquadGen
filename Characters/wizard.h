#ifndef WIZARD_H
#define WIZARD_H

#include "character.h"


class Wizard : public Character
{
public:
    Wizard(unsigned short, unsigned short, unsigned short, unsigned short, unsigned short, unsigned short);
    void useAbility(Character*) override;
};

#endif // WIZARD_H
