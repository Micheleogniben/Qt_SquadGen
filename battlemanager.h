#ifndef BATTLEMANAGER_H
#define BATTLEMANAGER_H

#include "character.h"
#include "move.h"
#include "squad.h"

#include <vector>

class BattleManager
{
private:
    Squad team1, team2;
    Character * main1, * main2;
    unsigned int turn;
public:
    explicit BattleManager(Squad &,Squad &);
    void setMain1(Character*);
    void setMain2(Character*);
    void initBattle(Character*, Character*);
    void attack(Move*);
    void ability();
    void removeDeadCharacter(std::string);
    void endBattle();
    unsigned int getTurn() const;
    void endTurnChecks();
};

#endif // BATTLEMANAGER_H
