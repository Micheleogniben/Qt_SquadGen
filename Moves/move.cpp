#include "move.h"
#include "character.h"

Move::Move(QString nm, QString dsc, Type tp, CharType chTp, unsigned short matk, unsigned short patk):
    name(nm), desc(dsc), type(tp), charType(chTp), magAtk(matk), phyAtk(patk) {}

Move::~Move() = default;

bool Move::isCompatible(const Character* character) const{
    if (type != Type::Nill){
        int tp = static_cast<int>(type);
        for (Type t : character->getTypes())
            if (tp == static_cast<int>(t))
                return true;
    }

    return charType == character->getCharType();
}


QString Move::getName() const{
    return name;
}

QString Move::getDescription() const{
    return desc;
}


Type Move::getType() const{
    return type;
}

unsigned short Move::getMagDmg() const{
    return magAtk;
}


unsigned short Move::getPhyDmg() const{
    return phyAtk;
}

QJsonObject Move::toJsonObj() const {
    QJsonObject moveObj;
    moveObj["name"] = name;
    moveObj["description"] = desc;
    moveObj["type"] = toText(type);
    moveObj["charType"] = toText(charType);
    moveObj["magAtk"] = magAtk;
    moveObj["phyAtk"] = phyAtk;
    return moveObj;
}
