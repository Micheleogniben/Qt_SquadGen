#ifndef BATTLEMANAGER_H
#define BATTLEMANAGER_H

#include <character.h>
#include <move.h>
#include <squad.h>
#include <QMessageBox>
#include <boss.h>
#include <random>
#include <movesmanager.h>
#include <vector>

class BattleManager
{
private:
    Squad* team1, * team2;
    unsigned int turn;
    void checkBurning(Squad*) const;
public:
    BattleManager(Squad*,Squad*);
    bool setTeam(Squad*,int);
    void setBossBattle(MovesManager*);
    void removeDeadCharacter(QString);
    int getTurn() const;
    void updateTurn();
    Squad* getTeam(int) const;
    int update();
    void removeDeadCharacters(Squad*);
    void opponentKombatLogic(Character*);
    void teamKombatLogic(Character*,Character*,Move*,QString);
    int turnLogic(Character*,Character*,Move*,QString);
    ~BattleManager();
};

#endif // BATTLEMANAGER_H
