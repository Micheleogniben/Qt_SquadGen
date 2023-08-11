#ifndef CHARACTERSPECIFICMOVE_H
#define CHARACTERSPECIFICMOVE_H

#include <move.h>

class CharacterSpecificMove: public Move
{
private:
    std::string Character;
public:
    explicit CharacterSpecificMove(std::string, std::string, unsigned int, unsigned int, std::string);
    ~CharacterSpecificMove() override;
};

#endif // CHARACTERSPECIFICMOVE_H
