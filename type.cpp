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
