#ifndef MOVE_H
#define MOVE_H

class Move{
private:
    std::string Name;
    std::string Description;
    unsigned int magicDmg;
    unsigned int physicalDmg;
public:
    explicit Move(std::string, std::string, unsigned int, unsigned int);
    virtual ~Move() = 0;
    const std::string getName();
    const std::string getDescription();
    const unsigned int getMagicDmg();
    const unsigned int getPhysicalDmg();
};

#endif
