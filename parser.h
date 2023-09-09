#ifndef PARSER_H
#define PARSER_H

#include "squad.h"

class Parser
{
public:
    Parser();
    static Squad* loadSquad(const QString& filePath);
    static void saveSquad(const QString& filePath, const Squad& squad);
    static Move* loadMove(const QString name, Character* character);


private:
    using CharacterLoaderType = std::map<CharType, std::function<Character*(const QString)>>;
    static CharacterLoaderType charLoader;
};


#endif // PARSER_H
