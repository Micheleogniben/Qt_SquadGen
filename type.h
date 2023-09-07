#ifndef TYPE_H
#define TYPE_H
#include <QString>
#include <QMap>

enum class Type{
    Earth,
    Fire,
    Air,
    Poison,
    Light,
    Neutral,
    Nill
};

enum class CharType{
    Dragon,
    Wizard,
    Cleric,
    Knight,
    Goblin,
    Nill
};

QString toText(Type tp);
QString toText(CharType chTp);

#endif // TYPE_H
