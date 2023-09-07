#include <type.h>

QString toText(Type tp){
    static QMap<Type, QString> typeToString = {
        {Type::Earth, "earth"},
        {Type::Fire, "fire"},
        {Type::Air, "air"},
        {Type::Poison, "poison"},
        {Type::Light, "light"},
        {Type::Neutral, "neutral"}
    };

    return typeToString.value(tp);
}

QString toText(CharType chTp){
    static QMap<CharType, QString> typeToString = {
        {CharType::Cleric, "Cleric"},
        {CharType::Dragon, "Dragon"},
        {CharType::Goblin, "Goblin"},
        {CharType::Knight, "Knight"},
        {CharType::Wizard, "Wizard"}
    };

    return typeToString.value(chTp);
}
