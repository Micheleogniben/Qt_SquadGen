#include "parser.h"

Parser::Parser()
{
    // Costruttore, se necessario
}

bool Parser::saveSquad(const QString& filePath, const Squad& squad)
{
    QJsonObject squadObject;

    // Popola l'oggetto JSON con i dati pertinenti della squadra
    squadObject["size"] = squad.getSize();
    squadObject["currentCapacity"] = squad.getCurrentCapacity();

    QJsonArray charactersArray;
    QJsonObject characterObject;

    // Itera attraverso i personaggi nella squadra
    for (Squad::Iterator it = squad.begin(); it != squad.end(); ++it)
    {
        Character* character = *it;


        // Popola characterObject con i dati del personaggio
        characterObject["name"] = character->getName();
        /*
        characterObject["phyAtk"] = character->getPhyAtk();
        characterObject["magAtk"] = character->getMagAtk();
        characterObject["phyDef"] = character->getPhyDef();
        characterObject["magDef"] = character->getMagDef();
        characterObject["speed"] = character->getSpeed();
        characterObject["lifePoints"] = character->getLifePoints();
        characterObject["weight"] = character->getWeight();
        characterObject["maxPS"] = character->getMaxPS();
        characterObject["isBurning"] = character->getBurnign();
        characterObject["abilityUsed"] = character->getAbilityUsed();
        */

        // Serializza il vettore di tipi come array di stringhe
        QJsonArray typesArray;
        for (const Type& type : character->getTypes())
        {
            typesArray.append(toText(type));
        }
        characterObject["types"] = typesArray;

        //charactersArray.append(character->toJson);
    }

    squadObject["characters"] = charactersArray;

    QJsonDocument doc(squadObject);
    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        // Gestisci l'errore se non è possibile aprire il file
        return false;
    }

    QTextStream stream(&file);
    stream << doc.toJson();
    file.close();

    return true;
}
