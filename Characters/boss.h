#ifndef BOSS_H
#define BOSS_H

#include <character.h>

class Boss: public Character
{
private:

public:
    Boss(QString);
    bool useAbility(Character*);

    static QString getAbilityDescription(){
        return QString("Minimizza l'attacco fisico di un avversario a scelta");
    }

    static const bool abilityFriendly=false;
    static const bool abilityHasTarget=true;

};

#endif // BOSS_H
