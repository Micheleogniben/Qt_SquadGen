#ifndef SQUAD_H
#define SQUAD_H

#include "character.h"

class Squad {
public:
    Squad();
    ~Squad();

    Character* getFront() const;
    Character* findByName(QString) const;

    void pop();
    bool addCharacter(Character*);

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
