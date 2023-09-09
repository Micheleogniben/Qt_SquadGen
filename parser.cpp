#include "parser.h"
#include "dragon.h"
#include "cleric.h"
#include "wizard.h"
#include "knight.h"
#include "goblin.h"
#include "movesmanager.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>

Parser::CharacterLoaderType Parser::charLoader = {
    {CharType::Dragon, [](const QString name) { return new Dragon(name); }},
    {CharType::Cleric, [](const QString name) { return new Cleric(name); }},
    {CharType::Wizard, [](const QString name) { return new Wizard(name); }},
    {CharType::Knight, [](const QString name) { return new Knight(name); }},
    {CharType::Goblin, [](const QString name) { return new Goblin(name, 1); }}
};


bool Parser::saveSquad(const QString& filePath, const Squad& squad) {
        QJsonObject squadObject;
        QJsonArray charactersArray;

        for (Squad::Iterator it = squad.begin(); it != squad.end(); ++it)
            charactersArray.append((*it)->toJsonObj());

        squadObject["characters"] = charactersArray;

        QJsonDocument doc(squadObject);
        QFile file(filePath);

        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return false;

        QTextStream stream(&file);
        stream << doc.toJson();
        file.close();

    return true;
}


Squad* Parser::loadSquad(const QString& filePath) {
    Squad* squad = new Squad();
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return squad;

    QTextStream stream(&file);
    QString jsonString = stream.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject squadObject = doc.object();

    QJsonArray charactersArray = squadObject["characters"].toArray();

    for (const QJsonValue& characterValue : charactersArray) {
        QJsonObject characterObject = characterValue.toObject();

        CharType characterType = toCharType(characterObject["characterType"].toString());

        // Verifica se il costruttore per il tipo di personaggio esiste nella mappa
        if (charLoader.find(characterType) != charLoader.end()) {
            Character* character = charLoader[characterType](characterObject["name"].toString());
            character->fromJsonObj(characterObject);

            squad->addCharacter(character);
        }
    }

    return squad;
}


Move* Parser::loadMove(const QString name) {
    for (Move* m : MovesManager::allMoves)
        if (m->getName() == name)
            return m;
    return nullptr;
}
