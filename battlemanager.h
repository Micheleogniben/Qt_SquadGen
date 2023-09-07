#ifndef BATTLEMANAGER_H
#define BATTLEMANAGER_H

#include <character.h>
#include <move.h>
#include <squad.h>

#include <vector>

class BattleManager
{
private:
    Squad* team1, * team2;
    unsigned int turn;
public:
    BattleManager(Squad*,Squad*);
    void attack(Move*);
    void ability();
    void removeDeadCharacter(QString);
    void endBattle();
    unsigned int getTurn() const;
    void endTurnChecks();
    Squad* getTeam(int) const;
};

#endif // BATTLEMANAGER_H
