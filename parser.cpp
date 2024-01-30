#include "parser.h"
#include "dragon.h"
#include "cleric.h"
#include "wizard.h"
#include "knight.h"
#include "goblin.h"
#include "movesmanager.h"
#include <stdexcept>
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


void Parser::saveSquad(const QString& filePath, const Squad& squad) {
        QJsonObject squadObject;
        QJsonArray charactersArray;

        for (Squad::Iterator it = squad.begin(); it != squad.end(); ++it)
            charactersArray.append((*it)->toJsonObj());

        squadObject["characters"] = charactersArray;

        QJsonDocument doc(squadObject);
        QFile file(filePath);

        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            throw std::runtime_error("Errore durante l'apertura del file per il salvataggio.");

        QTextStream stream(&file);
        stream << doc.toJson();
        file.close();
}


Squad* Parser::loadSquad(const QString& filePath) {
    Squad* squad = new Squad();
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw std::runtime_error("Error opening file for reading.");

    QTextStream stream(&file);
    QString jsonString = stream.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject squadObject = doc.object();

    QJsonArray charactersArray = squadObject["characters"].toArray();

    for (const QJsonValue& characterValue : charactersArray) {
        QJsonObject characterObject = characterValue.toObject();

        if (!characterObject.contains("name") || !characterObject.contains("characterType") || !characterObject.contains("move1") || !characterObject.contains("move2"))
            throw std::runtime_error("Invalid JSON format: Missing required fields for character.");

        CharType characterType = toCharType(characterObject["characterType"].toString());

        // Verifica se il costruttore per il tipo di personaggio esiste nella mappa
        if (charLoader.find(characterType) != charLoader.end()) {
            Character* character = charLoader[characterType](characterObject["name"].toString());
            character->fromJsonObj(characterObject);

            squad->addCharacter(character);
        } else{
            throw std::runtime_error("Invalid character type.");
        }
    }

    return squad;
}


Move* Parser::loadMove(const QString name, Character* character) {
    std::vector<Move*> compatibleMoves = MovesManager::getCompatibleMoves(character);

    // Cerca la mossa per nome nella lista delle mosse compatibili
    for (Move* m : compatibleMoves)
        if (m->getName() == name)
            return m;

    throw std::runtime_error("Move not found or incompatible with character type.");
    return nullptr;
}
