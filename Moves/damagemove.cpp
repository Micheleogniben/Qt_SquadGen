#include "damagemove.h"
#include "goblin.h"

DamageMove::DamageMove(QString name, QString description, unsigned short magicDmg, unsigned short physicalDmg, CharType chTp)
    : Move(name, description, Type::Nill, chTp, magicDmg, physicalDmg) { }

DamageMove::DamageMove(QString name, QString description, unsigned short magicDmg, unsigned short physicalDmg, Type type)
    : Move(name, description, type, CharType::Nill, magicDmg, physicalDmg) { }


// se le difese del nemico sono a zero mettiamo sotto alla frazione un numero n tale che 0 < n < 1, così che l'attacco nemico venga amplificato, ma senza incorrere nell'errore di una divisione per 0
unsigned short DamageMove::useMove(Character* attacker, Character* defender) const {
    double magAtk = static_cast<double>(attacker->getMagAtk()),
            phyAtk = static_cast<double>(attacker->getPhyAtk());

    double magDef = defender->getMagDef() ? defender->getMagDef() : 0.5,
            phyDef = defender->getPhyDef() ? defender->getPhyDef() : 0.5;

    double magCoeff = magAtk / magDef,
            phyCoeff = phyAtk / phyDef;

    unsigned short dmg = static_cast<unsigned short>(this->getMagDmg() * magCoeff + this->getPhyDmg() * phyCoeff);

    if (dynamic_cast<Goblin*>(attacker))
        dmg *= static_cast<Goblin*>(attacker)->getAmount();

    defender->setLifePoints(defender->getLifePoints() - dmg);
    return dmg;
}
