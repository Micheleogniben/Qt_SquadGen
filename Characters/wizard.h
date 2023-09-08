#ifndef WIZARD_H
#define WIZARD_H

#include "character.h"


class Wizard : public Character
{
public:
    Wizard(QString);
    Wizard(const Wizard&);
    bool useAbility(Character*) override;
};

#endif // WIZARD_H
