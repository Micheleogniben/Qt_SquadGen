#ifndef MOVE_H
#define MOVE_H

#include <Qstring>
#include "type.h"

class Character;

class Move{
private:
    QString name, desc;
    Type type;
    CharType charType;

public:
    Move(QString, QString, Type, CharType);
    bool isCompatible(const Character*) const;
    virtual void useMove(Character*, Character*) const =0;
    virtual ~Move();


    QString getName() const;
    QString getDescription() const;
    Type getType() const;
};

#endif
