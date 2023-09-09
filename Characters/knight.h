#ifndef KNIGHT_H
#define KNIGHT_H

#include "character.h"


class Knight : public Character
{
private:
public:
    Knight(QString);
    Knight(const Knight&);
    bool useAbility(Character*) override;
    static QString getAbilityDescription(){
        return QString("Infligge un attacco di potenza inversamente proporzionale ai suoi Life Points");
    }

    static const bool abilityFriendly=false;
    static const bool abilityHasTarget=true;
};

#endif // KNIGHT_H
