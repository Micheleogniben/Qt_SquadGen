#ifndef CLERIC_H
#define CLERIC_H

#include "character.h"


class Cleric : public Character
{
private:
    static const bool abilityFriendly=true;
    static const bool abilityHasTarget=true;
public:
    Cleric(QString);
    Cleric(const Cleric&);
    bool useAbility(Character*) override;


    static QString getAbilityDescription(){
        return QString("Restaura e raddoppia i Life Points di un tuo compagno di squadra");
    }
};

#endif // CLERIC_H
