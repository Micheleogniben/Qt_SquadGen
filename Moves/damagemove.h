#ifndef DAMAGEMOVE_H
#define DAMAGEMOVE_H
#include "move.h"


class DamageMove : public Move
{
public:
    DamageMove(QString, QString, unsigned short, unsigned short, CharType);
    DamageMove(QString, QString, unsigned short, unsigned short, Type);
    unsigned short useMove(Character*, Character*) const override;
};

#endif // DAMAGEMOVE_H
