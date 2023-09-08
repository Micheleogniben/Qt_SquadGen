#include "squad.h"
#include "cleric.h"
#include "dragon.h"
#include "goblin.h"
#include "knight.h"
#include "type.h"
#include "wizard.h"

Squad::Squad() : head(nullptr), size(0), currentWeight(0) {}

Squad::Squad(const Squad& other) : head(nullptr), size(0), currentWeight(0) {
    // Copia i personaggi da other in questa istanza
    Node* otherCurrent = other.head;
    Node* thisPrevious = nullptr;

    Character* newCharacter;


    while (otherCurrent) {
        Character* otherCharacter = otherCurrent->data;

        // Crea un nuovo Character con copia profonda
        switch (otherCharacter->getCharType()) {
        case CharType::Cleric:
            newCharacter = new Cleric(static_cast<Cleric&>(*otherCharacter));
            break;
        case CharType::Wizard:
            newCharacter = new Wizard(static_cast<Wizard&>(*otherCharacter));
            break;
        case CharType::Knight:
            newCharacter = new Knight(static_cast<Knight&>(*otherCharacter));
            break;
        case CharType::Dragon:
            newCharacter = new Dragon(static_cast<Dragon&>(*otherCharacter));
            break;
        case CharType::Goblin:
            newCharacter = new Goblin(static_cast<Goblin&>(*otherCharacter));
            break;
        default:
            newCharacter = nullptr;
            break;
        }

        if (newCharacter){
            // Crea un nuovo nodo per il nuovo Character
            Node* newNode = new Node(newCharacter);

            // Collega il nuovo nodo alla lista
            if (thisPrevious) {
                thisPrevious->next = newNode;
            } else {
                head = newNode;
            }

            // Avanza ai prossimi nodi nella lista originale e in questa copia
            thisPrevious = newNode;

            // Aggiorna le dimensioni
            size++;
            currentWeight += newCharacter->getWeight(); // Assumi che ci sia un metodo getWeight() per Character
        } else {
            // Avanza ai prossimi nodi nella lista originale e in questa copia
            thisPrevious = otherCurrent;
        }
        otherCurrent = otherCurrent->next;
    }
}


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
    if (currentWeight + data->getWeight() <= capacity && !isNameTaken(data->getName())) {
        Node* newNode = new Node(data);
        newNode->next = nullptr; // Assicura che il campo "next" del nuovo nodo sia inizializzato a nullptr
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


bool Squad::deleteByName(QString name) {
    Node* current = head;
    Node* previous = nullptr;

    while (current != nullptr) {
        if (current->data->getName().compare(name, Qt::CaseInsensitive) == 0) {
            // Trovato il personaggio da eliminare

            if (previous == nullptr) {
                pop();
                return true;
            } else {
                // Il personaggio da eliminare è in mezzo o alla fine della lista
                previous->next = current->next;
            }

            currentWeight -= current->data->getWeight();
            delete current->data;
            delete current;
            size--;
            return true;
        }

        previous = current;
        current = current->next;
    }

    return false; // Personaggio non trovato
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
        if (current->data->getName().compare(name, Qt::CaseInsensitive) == 0) {
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
    return findByName(name) != nullptr;
}

int Squad::getSize() const {
    return size;
}

unsigned short Squad::getCurrentCapacity() const {
    return capacity - currentWeight;
}
