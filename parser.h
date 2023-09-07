#ifndef PARSER_H
#define PARSER_H

#include "squad.h"

class Parser
{
public:
    Parser();
    Squad loadSquad(const QString& filePath);
    bool saveSquad(const QString& filePath, const Squad& squad);
    static Move* loadMove(const QJsonObject& moveObject);

private:
    std::map<QString, std::function<Character*()>> charLoader;
};


#endif // PARSER_H
