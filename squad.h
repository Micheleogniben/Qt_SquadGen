#ifndef SQUAD_H
#define SQUAD_H

#include "character.h"
/*#include <vector>

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
*/

class Squad {
public:
    Squad();
    ~Squad();

    Character* getFront() const;
    Character* findByName(QString) const;

    void pop();
    void addCharacter(Character*);
    bool pushBack(Character*);

    bool isEmpty() const;
    bool isNameTaken(QString);

    int getSize() const;
    unsigned short getWeight() const;


    class Iterator;

    Iterator begin() const;
    Iterator end() const;


    const static unsigned short capacity = 50;

private:
    struct Node {
        Character* data;
        Node* next;

        Node(Character* d) : data(d), next(nullptr) {}
    };

    Node *head;
    unsigned short size, currentWeight;
};


class Squad::Iterator {
public:
    Iterator(Node* start);

    bool operator==(const Iterator& other) const;
    bool operator!=(const Iterator& other) const;
    Iterator& operator++();
    Character* operator*();

private:
    Node* current;
};


#endif // SQUAD_H
