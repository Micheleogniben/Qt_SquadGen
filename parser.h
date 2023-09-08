#ifndef PARSER_H
#define PARSER_H

#include "squad.h"

class Parser
{
public:
    Parser();
    static Squad* loadSquad(const QString& filePath);
    static bool saveSquad(const QString& filePath, const Squad& squad);
    static Move* loadMove(const QString name);


private:
    using CharacterLoaderType = std::map<CharType, std::function<Character*(const QString)>>;
    static CharacterLoaderType charLoader;
};


#endif // PARSER_H
