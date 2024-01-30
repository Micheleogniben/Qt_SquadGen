#include "goblin.h"
#include <cmath>


Goblin::Goblin(QString name, unsigned short a) : Character(goblinStats, name), amount(a) {
    Character::setLifePoints(getMaxPS() * amount);
}

Goblin::Goblin(const Goblin& other) : Character(other), amount(other.amount) { };

// L'abilità dei goblin consiste nell'aumentare del 10% ad ogni turno l'attacco, sia magico che fisico
bool Goblin::useAbility(Character*){
    setPhyAtk(getPhyAtk() * 0.4 + getPhyAtk());
    setMagAtk(getMagAtk() * 0.4 + getMagAtk());
    setAbilityUsed(true);
    return true;
}

// la funzione std::ceil arrotonda per eccesso i numeri con parte frazionaria maggiore di 0, in questo modo
// aggiungo nu goblin se il risultato è decimale, perché questo significherebbe che ho un goblin in più con poca vita
void Goblin::setLifePoints(const short lifePts){
    Character::setLifePoints(lifePts);
    setAmount(std::ceil(lifePts / getMaxPS()));
}

unsigned short Goblin::getAmount() const{
    return amount;
}

void Goblin::setAmount(unsigned short newValue){
    amount = newValue;
}


QJsonObject Goblin::toJsonObj() const{
    QJsonObject characterObj = Character::toJsonObj();
    characterObj["amount"] = amount;
    //characterObj["lifePts"] = amount * getMaxPS();
    return characterObj;
}

void Goblin::fromJsonObj(QJsonObject characterObj){
    if (!characterObj.contains("amount"))
        throw std::runtime_error("Formato JSON non valido: mancano dei campi necessari al caricamento di Goblin.");

    Character::fromJsonObj(characterObj);
    setLifePoints(characterObj["amount"].toInt() * goblinStats.lifePts);
}

unsigned short Goblin::getWeight() const {
    return amount * goblinStats.weight;
}


