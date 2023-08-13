#ifndef MOVE_H
#define MOVE_H

#include <string>
#include "type.h"


class Move{
private:
    std::string Name, Description;
    unsigned int phyDmg, magDmg;
    Type type;
public:
    Move(std::string, std::string, unsigned int, unsigned int, Type);
    std::string getName() const;
    std::string getDescription() const;
    unsigned int getDamage() const;
    Type getType() const;
};

#endif
