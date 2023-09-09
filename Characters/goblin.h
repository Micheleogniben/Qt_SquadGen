#ifndef GOBLIN_H
#define GOBLIN_H

#include "character.h"


class Goblin : public Character
{
private:
    unsigned short amount;
    static const bool abilityFriendly=true;
    static const bool abilityHasTarget=false;
public:
    Goblin(QString, unsigned short);
    Goblin(const Goblin&);
    bool useAbility(Character*) override;
    void setLifePoints(const unsigned short) override;

    unsigned short getAmount() const;
    void setAmount(unsigned short);

    QJsonObject toJsonObj() const override;


    static QString getAbilityDescription(){
        return QString("Potenziamento attacco fisico e magico");
    }
};

#endif // GOBLIN_H
