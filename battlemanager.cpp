#include "battlemanager.h"

BattleManager::BattleManager(Squad* s1, Squad* s2)
    : team1(s1), team2(s2)
{
    turn = 0;
}

Squad* BattleManager::getTeam(int i)const{
    if(i==1) return team1;
    if(i==2) return team2;
    else return nullptr;
}
