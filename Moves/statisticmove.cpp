#include "statisticmove.h"
#include "character.h"

StatisticMove::StatisticMove(QString name, QString description, StatisticChanges statChange, CharType chTp)
    : Move(name, description, Type::Nill, chTp), changes(statChange) {}

StatisticMove::StatisticMove(QString name, QString description, StatisticChanges statChange, Type type)
    : Move(name, description, type, CharType::Nill), changes(statChange) {}


void StatisticMove::useMove(Character* attacker, Character* defender) const {
    unsigned short magAtk = attacker->getMagAtk(),
            magDef = defender->getMagDef(),
            coeff = magAtk / magDef;

    defender->setMagAtk(defender->getMagAtk() - changes.magicAtkChange * coeff);
    defender->setPhyAtk(defender->getPhyAtk() - changes.physicalAtkChange * coeff);
    defender->setMagDef(defender->getMagDef() - changes.magicDefChange * coeff);
    defender->setPhyDef(defender->getPhyDef() - changes.physicalDefChange * coeff);
    defender->setSpeed(defender->getSpeed() - changes.speedChange * coeff);
}
