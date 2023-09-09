#include "battlemanager.h"

BattleManager::BattleManager(Squad* s1, Squad* s2)
{
    if(s1) team1 = new Squad(*s1);
    if(s2) team2 = new Squad(*s2);
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

int BattleManager::update() {
    removeDeadCharacters(team1);
    removeDeadCharacters(team2);

    checkBurning(team1);
    checkBurning(team2);

    if (team1->getSize()==0) {
        return 1;
    }

    if (team2->getSize()==0) {
        return 2;
    }
    return 0;
}

void BattleManager::removeDeadCharacters(Squad* team) {
    for (Character* character: *team) {
        if (character->getLifePoints() <= 0) {
            QString name = character->getName();
            team->deleteByName(name);
            QMessageBox::warning(nullptr, "Personaggio Morto", name + " è morto");
            break;
        }
    }
}


BattleManager::~BattleManager(){
    if(team1) delete team1;
    if(team2) delete team2;
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
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<int> distribution(min, max);

    return distribution(engine);
}

void BattleManager::setBossBattle(MovesManager* m){
    if(team2) delete team2;
    team2 = new Squad();
    Character* boss=new Boss("Vordt della Valle Boreale");
    boss->addMove(m->moveByName(QString("Abyss")),m->moveByName(QString("God's tear")));
    team2->addCharacter(boss);
}

int BattleManager::turnLogic(Character *attacker, Character *target, Move *move, QString action){

    Character* opponent = nullptr;

    int i = getRandomInt(0,team2->getSize()-1);
    for(Character* character: *team2){
        if(i==0) opponent=character;
        i--;
    }

    int toReturn;

    if(attacker->getSpeed()>=opponent->getSpeed()){
        QMessageBox::warning(nullptr,"Primo attacco",attacker->getName() + " é piú veloce di " + opponent->getName() +", attaccherá per primo");
        QString name = opponent->getName();
        teamKombatLogic(attacker,target,move,action);
        toReturn = update();
        if(!team2->findByName(name)){
            QMessageBox::warning(nullptr,"Morte Prematura",name + " é morto prima di poter eseguire il suo attacco");
            return toReturn;
        }
        opponentKombatLogic(opponent);
    }

    else{
        QMessageBox::warning(nullptr,"Primo attacco", opponent->getName() + " é piú veloce di " + attacker->getName() +", attaccherá per primo");
        QString name = attacker->getName();
        opponentKombatLogic(opponent);
        toReturn=update();
        if(!team1->findByName(name)){
            QMessageBox::warning(nullptr,"Morte Prematura",name + " é morto prima di poter eseguire il suo attacco");
            return toReturn;
        }
        teamKombatLogic(attacker,target,move,action);
    }
    return update();
}

void BattleManager::teamKombatLogic(Character *attacker, Character *target, Move *move, QString action){
    if(action == "Move"){
        QMessageBox::warning(nullptr, "Attacco eseguito", attacker->getName() + " ha usato " + move->getName() + " colpendo " +target->getName());
        QMessageBox::warning(nullptr,"Mossa eseguita","Danni inflitti: "+ QString::number(move->useMove(attacker,target)));
    }
    else if(action == "Ability"){
        if(target){
            attacker->useAbility(target);
            QMessageBox::warning(nullptr, "Abilitá usata correttamente" , attacker->getName() + " ha usato la sua abilitá su " + target->getName() );
        }
        else{
            attacker->useAbility(nullptr);
            QMessageBox::warning(nullptr, "Abilitá usata correttamente" , attacker->getName() + " ha usato la sua abilitá");
        }
    }
    else QMessageBox::critical(nullptr,"Fatal Error","There was a problem, the action does not have an implementation");
}

void BattleManager::opponentKombatLogic(Character* attacker){

    QMessageBox::warning(nullptr, "Brutte Notizie", "Ora é il turno del tuo avversario");

    if(!team1 || !team2) return;
    if(team1 && team1->getSize()==0) return;
    if(team2 && team2->getSize()==0) return;

    const Move* move = nullptr;
    Character* target = nullptr;

    int i=getRandomInt(0,team1->getSize()-1);
    for(Character* character: *team1){
        if(i==0) target = character;
        i--;
    }

    bool abilityYetUse=attacker->getAbilityUsed();
    i=getRandomInt(0,1);

    if(!abilityYetUse && i==0){
        attacker->useAbility(target);
        QMessageBox::warning(nullptr, "Abilitá usata correttamente", attacker->getName() + " ha usato la sua abilitá colpendo " +target->getName() + "\n Descrizione: " + Boss::getAbilityDescription());
    }

    else{
        i=getRandomInt(0,1);
        if(i==1) move = std::get<0>(attacker->getMoves());
        else move = std::get<1>(attacker->getMoves());

        if(attacker && move && target){
            QMessageBox::warning(nullptr, "Attacco eseguito", attacker->getName() + " ha usato " + move->getName() + " colpendo " +target->getName());
            QMessageBox::warning(nullptr,"Mossa eseguita","Danni inflitti: "+ QString::number(move->useMove(attacker,target)));
        }
    }
}

void BattleManager::checkBurning(Squad* s) const {
    // se ci sono personaggi con effetto bruciatura si toglie un lieve danno
    for (Character* character : *s) {
        if (character->getBurnign() > 0) {
            character->setLifePoints(character->getLifePoints() * 0.8);
            character->setBurning(character->getBurnign() - 1);
        }
    }
}
