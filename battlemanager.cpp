#include "battlemanager.h"

BattleManager::BattleManager(Squad* s1, Squad* s2)
{
    team1 = s1;
    team2 = s2;
    turn = 0;
}

Squad* BattleManager::getTeam(int i)const{
    if(i==1) return team1;
    if(i==2) return team2;
    else return nullptr;
}

int BattleManager::getTurn() const{
    return turn;
}

void BattleManager::updateTurn(){
    turn++;
}

void BattleManager::update() {
    removeDeadCharacters(team1);
    removeDeadCharacters(team2);

    if (team1->isEmpty()) {
        QMessageBox::warning(nullptr, "Loss", "HAI PERSO");
    }

    if (team2->isEmpty()) {
        QMessageBox::warning(nullptr, "Victory", "HAI VINTO");
    }
}

void BattleManager::removeDeadCharacters(Squad* team) {
    for (auto character: *team) {
        if (character->getLifePoints() < 0) {
            delete character;
            //team->;
            QMessageBox::warning(nullptr, "Personaggio Morto", character->getName() + " è morto");
        }
    }
}


BattleManager::~BattleManager(){
    for(auto character: *team1) delete character;
    for(auto character: *team2) delete character;
}
