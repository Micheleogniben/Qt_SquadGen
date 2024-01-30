#ifndef WIZARD_H
#define WIZARD_H

#include "character.h"


class Wizard : public Character
{
private:
public:
    Wizard(QString);
    Wizard(const Wizard&);
    bool useAbility(Character*) override;

    static QString getAbilityDescription(){
        return QString("Riduce del 30% tutte le statistiche di un avversario");
    }
    static const bool abilityFriendly=false;
    static const bool abilityHasTarget=true;
};

#endif // WIZARD_H
