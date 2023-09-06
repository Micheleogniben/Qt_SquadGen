#include "battlemanager.h"

BattleManager::BattleManager(Squad* s1)
    : team1(s1), team2(nullptr)
{
    turn = 0;
}


unsigned int BattleManager::getTurn() const{
    return turn;
}

void BattleManager::endTurnChecks(){

}

void BattleManager::attack(Move*){
    if(turn%2==1){

    }
    else{

    }
    endTurnChecks();
    turn++;
}
