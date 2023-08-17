#include "battlemanager.h"

BattleManager::BattleManager(Squad & s1, Squad & s2)
    : team1(s1), team2(s2)
{
    turn = 0;
}

void BattleManager::setMain1(Character * c){
    main1=c;
}

void BattleManager::setMain2(Character * c){
    main2=c;
}

void BattleManager::initBattle(Character* c1, Character* c2)
{
   setMain1(c1);
   setMain2(c2);
    turn++;
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
