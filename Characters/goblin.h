#ifndef GOBLIN_H
#define GOBLIN_H

#include "character.h"


class Goblin : public Character
{
private:
    unsigned short amount;
public:
    Goblin(QString, unsigned short);
    Goblin(const Goblin&);
    bool useAbility(Character*) override;
    unsigned short getWeight() const override;
    void setLifePoints(const short) override;

    unsigned short getAmount() const;
    void setAmount(unsigned short);

    QJsonObject toJsonObj() const override;
    void fromJsonObj(QJsonObject characterObj) override;

    static QString getAbilityDescription(){
        return QString("Potenziamento attacco fisico e magico");
    }

    static const bool abilityFriendly=true;
    static const bool abilityHasTarget=false;
};

#endif // GOBLIN_H
