#ifndef MOVE_H
#define MOVE_H

#include "QtCore/qjsonobject.h"
#include "type.h"

class Character;

class Move{
private:
    QString name, desc;
    Type type;
    CharType charType;
    unsigned short magAtk, phyAtk;

public:
    Move(QString, QString, Type, CharType, unsigned short, unsigned short);
    bool isCompatible(const Character*) const;
    virtual void useMove(Character*, Character*) const =0;
    virtual ~Move();


    QString getName() const;
    QString getDescription() const;
    unsigned short getPhyDmg() const;
    unsigned short getMagDmg() const;
    Type getType() const;

    virtual QJsonObject toJsonObj() const;
};

#endif
