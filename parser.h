#ifndef PARSER_H
#define PARSER_H

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QString>
#include "squad.h"  // Includi il tuo header per la classe Squad

class Parser
{
public:
    // Costruttore
    Parser();

    // Metodo per caricare una squadra da un file JSON
    Squad loadSquad(const QString& filePath);

    // Metodo per salvare una squadra in un file JSON
    bool saveSquad(const QString& filePath, const Squad& squad);

private:
    // Funzione di utilità per il parsing di una squadra da un oggetto JSON
    Squad parseSquad(const QJsonObject& squadObject);
};


#endif // PARSER_H
