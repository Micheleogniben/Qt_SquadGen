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

bool isEqual(Type tp, QString str) {
    static QMap<Type, QString> typeToString = {
        {Type::Earth, "earth"},
        {Type::Fire, "fire"},
        {Type::Air, "air"},
        {Type::Poison, "poison"},
        {Type::Light, "light"},
        {Type::Neutral, "neutral"}
    };

    return str.toLower() == typeToString.value(tp).toLower();
}

enum class CharType{
    Dragon,
    Wizard,
    Cleric,
    Knight,
    Goblin,
    Nill
};

#endif // TYPE_H
