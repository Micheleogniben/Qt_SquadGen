#include <QJsonArray>

#include "character.h"
#include "type.h"
#include "parser.h"

// CONSTRUCTOR AND DESTRUCTOR
Character::Character(DefaultStats d, QString n) :
    maxPS(d.lifePts), burningTurns(0), abilityUsed(false), name(n), stats{d.magAtk, d.phyAtk, d.magDef, d.phyDef, d.speed, d.weight, d.lifePts, d.types, d.charType}  { };


Character::Character(const Character& other)
    : maxPS(other.maxPS),
      burningTurns(other.burningTurns),
      abilityUsed(other.abilityUsed),
      moves(other.moves),
      name(other.name),
      stats(other.stats) { };

Character::~Character() = default;

void Character::addMove(const Move* m1, const Move* m2){
    moves = {m1, m2};
}

// GET METHODS
unsigned short Character::getPhyAtk() const{
    return stats.physicalAtk;
}

unsigned short Character::getMagAtk() const{
    return stats.magicAtk;
}

unsigned short Character::getPhyDef() const{
    return stats.physicalDef;
}

unsigned short Character::getMagDef() const{
    return stats.magicDef;
}

unsigned short Character::getSpeed() const{
    return stats.speed;
}

unsigned short Character::getLifePoints() const{
    return stats.lifePoints;
}

unsigned short Character::getWeight() const{
    return stats.weight;
}

unsigned short Character::getMaxPS() const{
    return maxPS;
}

unsigned short Character::getBurnign() const{
    return burningTurns;
}

bool Character::getAbilityUsed() const{
    return abilityUsed;
}

std::vector<Type> Character::getTypes() const{
    return stats.types;
}

CharType Character::getCharType() const{
    return stats.charType;
}

QString Character::getMovesNames() const{
    QString movesNames="";
    const Move* move1 = std::get<0>(moves);
    const Move* move2 = std::get<1>(moves);
    if (move1 && move2)
        movesNames=move1->getName() + ", " + move2->getName();
    return movesNames;
}

QString Character::getName() const{
    return name;
}


// SET METHODS
void Character::setPhyAtk(const unsigned short amount){
    stats.physicalAtk = amount < 0 ? 0 : amount > 10 ? 10 : amount;
}

void Character::setMagAtk(const unsigned short amount){
    stats.magicAtk = amount < 0 ? 0 : amount > 10 ? 10 : amount;
}

void Character::setMagDef(const unsigned short amount){
    stats.magicDef = amount < 0 ? 0 : amount > 10 ? 10 : amount;
}

void Character::setPhyDef(const unsigned short amount){
    stats.physicalDef = amount < 0 ? 0 : amount > 10 ? 10 : amount;
}

void Character::setSpeed(const unsigned short amount){
    stats.speed = amount < 0 ? 0 : amount > 10 ? 10 : amount;
}

void Character::setBurning(const unsigned short turns){
    burningTurns = turns;
}

void Character::setAbilityUsed(const bool val){
    abilityUsed = val;
}

void Character::setLifePoints(const short amount){
    stats.lifePoints = amount < 0 ? 0 : amount;
}

void Character::clearMoves(){
    moves = {};
}

QJsonObject Character::toJsonObj() const {
    QJsonObject characterObj;

    characterObj["name"] = name;
    characterObj["characterType"] = toText(getCharType());
    characterObj["move1"] = std::get<0>(moves)->getName();
    characterObj["move2"] = std::get<1>(moves)->getName();

    return characterObj;
}

void Character::fromJsonObj(QJsonObject characterObj){
    QString loadedName = characterObj["name"].toString();
    QString move1Obj = characterObj["move1"].toString();
    QString move2Obj = characterObj["move2"].toString();

    // Crea istanze delle mosse dai loro oggetti JSON

    Move* move1 = Parser::loadMove(move1Obj, this);
    Move* move2 = Parser::loadMove(move2Obj, this);

    name = loadedName;
    moves = {move1, move2};
}


std::tuple<const Move*, const Move*> Character::getMoves() const{
    return moves;
}
