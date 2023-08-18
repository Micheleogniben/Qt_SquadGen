#ifndef CHARACTERSPECIFICMOVE_H
#define CHARACTERSPECIFICMOVE_H

#include "move.h"
#include <map>

class CharacterSpecificMove: public Move
{
private:
    CharType charType;

public:
    CharacterSpecificMove(std::string, std::string, unsigned int, unsigned int, Type tp, CharType);
    ~CharacterSpecificMove();
    bool isCompatible(const Character*) const override;
};

#endif // CHARACTERSPECIFICMOVE_H
