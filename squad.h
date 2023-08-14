#ifndef SQUAD_H
#define SQUAD_H

#include <character.h>

#include <vector>

class Squad
{
private:
    std::vector<Character*> components;
    std::string name;
    static const unsigned int capacity = 50;
public:
    explicit Squad(std::string, std::vector<Character*>);
    void removeCharacter(Character*);
    void addCharacter(Character*);
};

#endif // SQUAD_H
