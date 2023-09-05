#include "move.h"
#include "character.h"

Move::Move(QString nm, QString dsc, Type tp, CharType chTp):
    name(nm), desc(dsc), type(tp), charType(chTp) {}

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
