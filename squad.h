#ifndef SQUAD_H
#define SQUAD_H

#include <character.h>

#include <vector>

class Squad
{
private:
    std::vector<Character*> components;
    std::string name;
public:
    Squad();
    static const unsigned int capacity = 50;
    explicit Squad(std::string, std::vector<Character*>);
    void removeCharacter(Character*);
    void addCharacter(Character*);
    void setName(std::string);
    unsigned int weight() const;
};

#endif // SQUAD_H
