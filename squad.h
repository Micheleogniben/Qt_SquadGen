#ifndef SQUAD_H
#define SQUAD_H

#include "character.h"
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
    bool isEmpty() const;

    class iterator
    {
    private:
        std::vector<Character*>::iterator it;

    public:
        iterator(std::vector<Character*>::iterator iter) : it(iter) {}
        iterator operator++() { return iterator(++it); }
        iterator operator--() { return iterator(--it); }
        Character* operator*() { return *it; }
        bool operator==(const iterator& other) const { return it == other.it; }
        bool operator!=(const iterator& other) const { return it != other.it; }
    };

    iterator begin()
    {
        return iterator(components.begin());
    }

    iterator end()
    {
        return iterator(components.end());
    }
};

#endif // SQUAD_H
