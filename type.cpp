#include "type.h"

QString toText(Type tp){
    static QMap<Type, QString> typeToString = {
        {Type::Nill, ""},
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
    static QMap<CharType, QString> stringToCharType = {
        {CharType::Nill,   ""},
        {CharType::Cleric, "Cleric"},
        {CharType::Dragon, "Dragon"},
        {CharType::Goblin, "Goblin"},
        {CharType::Knight, "Knight"},
        {CharType::Wizard, "Wizard"}
    };

    return stringToCharType.value(chTp);
}


Type toType(QString s){
    static QMap<QString, Type> stringToType = {
        {"", Type::Nill},
        {"earth", Type::Earth},
        {"fire", Type::Fire},
        {"air", Type::Air},
        {"poison", Type::Poison},
        {"light", Type::Light},
        {"neutral", Type::Neutral}
    };

    return stringToType.value(s);
}

CharType toCharType(QString s){
    static QMap<QString, CharType> stringToCharType = {
        {"",       CharType::Nill},
        {"Cleric", CharType::Cleric},
        {"Dragon", CharType::Dragon},
        {"Goblin", CharType::Goblin},
        {"Knight", CharType::Knight},
        {"Wizard", CharType::Wizard}
    };

    return stringToCharType.value(s);
}
