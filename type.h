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

QString toText(Type tp);

enum class CharType{
    Dragon,
    Wizard,
    Cleric,
    Knight,
    Goblin,
    Nill
};

#endif // TYPE_H
