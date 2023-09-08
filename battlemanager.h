#ifndef BATTLEMANAGER_H
#define BATTLEMANAGER_H

#include <character.h>
#include <move.h>
#include <squad.h>
#include <QMessageBox>

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
    int getTurn() const;
    void updateTurn();
    Squad* getTeam(int) const;
    void update();
    void removeDeadCharacters(Squad*);
    ~BattleManager();
};

#endif // BATTLEMANAGER_H
