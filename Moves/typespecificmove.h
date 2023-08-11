#ifndef TYPESPECIFICMOVE_H
#define TYPESPECIFICMOVE_H

#include <move.h>

class TypeSpecificMove:public Move
{
private:
    std::string Type;
public:
    explicit TypeSpecificMove(std::string, std::string, unsigned int, unsigned int, std::string);
    const std::string getType();
    ~TypeSpecificMove() override;
};

#endif // TYPESPECIFICMOVE_H
