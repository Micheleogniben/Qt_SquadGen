#ifndef DRAGON_H
#define DRAGON_H

#include "character.h"


class Dragon : public Character
{
private:
    static const bool abilityFriendly=false;
    static const bool abilityHasTarget=true;
public:
    Dragon(QString);
    Dragon(const Dragon&);
    bool useAbility(Character*) override;

    static QString getAbilityDescription(){
        return QString("Toglie 30% di vita ad un avversario e provoca un effetto bruciatura. L'effetto di bruciatura infligge danno per un numero randomico di turni");
    }
};

#endif // DRAGON_H
