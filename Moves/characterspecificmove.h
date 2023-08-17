#ifndef CHARACTERSPECIFICMOVE_H
#define CHARACTERSPECIFICMOVE_H

#include "move.h"

class CharacterSpecificMove: public Move
{
private:
    std::string character;
public:
    CharacterSpecificMove(std::string, std::string, unsigned int, unsigned int, Type tp, std::string);
};

#endif // CHARACTERSPECIFICMOVE_H
