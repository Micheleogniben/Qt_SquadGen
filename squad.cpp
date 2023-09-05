#include "squad.h"

Squad::Squad() : head(nullptr), size(0), currentWeight(0) {}

Squad::~Squad() {
    while (!isEmpty())
        pop();
}



Squad::Iterator::Iterator(Squad::Node* start) : current(start) {}

Squad::Iterator Squad::begin() const {
    return Iterator(head);
}

Squad::Iterator Squad::end() const {
    return Iterator(nullptr);
}

bool Squad::Iterator::operator==(const Iterator& other) const {
    return current == other.current;
}

bool Squad::Iterator::operator!=(const Iterator& other) const {
    return !(*this == other);
}

Squad::Iterator& Squad::Iterator::operator++() {
    if (current)
        current = current->next;

    return *this;
}

Character* Squad::Iterator::operator*() {
    if (current)
        return current->data;

    return nullptr; // Nessun elemento rimanente
}


bool Squad::addCharacter(Character* data) {
    if (currentWeight + data->getWeight() <= 50 && isNameTaken(data->getName())) {
        Node* newNode = new Node(data);
        if (isEmpty()) {
            head = newNode;
        } else {
            // Trova l'ultimo nodo e collega il nuovo nodo
            Node* lastNode = head;
            while (lastNode->next != nullptr)
                lastNode = lastNode->next;

            lastNode->next = newNode;
        }

        size++;
        currentWeight += data->getWeight();
        return true;
    }
    return false;
}


void Squad::pop() {
    if (!isEmpty()) {
        Node* temp = head;
        head = head->next;
        currentWeight -= temp->data->getWeight();
        delete temp->data;
        delete temp;
        size--;
    }
}

Character* Squad::findByName(QString name) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->data->getName() == name) {
            return current->data;
        }
        current = current->next;
    }
    return nullptr; // Personaggio non trovato
}


Character* Squad::getFront() const {
    if (!isEmpty())
        return head->data;

    return nullptr;
}


bool Squad::isEmpty() const {
    return size == 0;
}

bool Squad::isNameTaken(QString name){
    return findByName(name) == nullptr;
}

int Squad::getSize() const {
    return size;
}

unsigned short Squad::getWeight() const {
    return currentWeight;
}
