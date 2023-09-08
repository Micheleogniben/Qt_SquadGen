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
    for (Character* character: *team) {
        if (character->getLifePoints() <= 0) {
            team->deleteByName(character->getName());
            QMessageBox::warning(nullptr, "Personaggio Morto", character->getName() + " è morto");
        }
    }
}


BattleManager::~BattleManager(){
    for(auto character: *team1) delete character;
    for(auto character: *team2) delete character;
}

bool BattleManager::setTeam(Squad* team, int i){
    if(i==1){
        team1=team;
        return true;
    }
    if(i==1){
        team2=team;
        return true;
    }
    return false;
}

int getRandomInt(int min, int max) {
    std::random_device rd; // Obtain a random seed from the operating system
    std::mt19937 engine(rd()); // Mersenne Twister pseudo-random number generator
    std::uniform_int_distribution<int> distribution(min, max); // Define the distribution

    return distribution(engine); // Generate and return a random integer
}

void BattleManager::setBossBattle(MovesManager* m){
    if(team2) delete team2;
    team2 = new Squad();
    Character* boss=new Boss("Gorlock The Destroyer");
    boss->addMove(m->moveByName(QString("Abyss")),m->moveByName(QString("God's tear")));
    team2->addCharacter(boss);
}

void BattleManager::opponentKombatLogic(){

    if(!team1 || !team2) return;
    if(team1 && team1->getSize()==0) return;
    if(team2 && team2->getSize()==0) return;

    Character* attacker = nullptr;
    const Move* move = nullptr;
    Character* target = nullptr;

    int i = getRandomInt(0,team2->getSize()-1);
    for(Character* character: *team2){
        if(i==0) attacker=character;
        i--;
    }
    i=getRandomInt(0,1);
    if(i==1) move = std::get<0>(attacker->getMoves());
    else move = std::get<1>(attacker->getMoves());

    i=getRandomInt(0,team1->getSize()-1);
    for(Character* character: *team1){
        if(i==0) target = character;
        i--;
    }
    if(attacker && move && target){
        move->useMove(attacker,target);
        QMessageBox::warning(nullptr, "Attack executed", attacker->getName() + " used " + move->getName() + " targeting " +target->getName());
        update();
    }
}
