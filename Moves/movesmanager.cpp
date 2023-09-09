#include "movesmanager.h"
#include "statisticmove.h"
#include "damagemove.h"

std::vector<Move*> MovesManager::allMoves;

MovesManager::MovesManager(){
    // Mosse DamageMove
    addMove(new DamageMove("Fire Bolt", "Spara un proiettile di fuoco.", 15, 5, Type::Fire));
    addMove(new DamageMove("Ice Spike", "Lancia uno spike di ghiaccio.", 12, 8, Type::Air));
    addMove(new DamageMove("Poison Dart", "Scaglia una freccia avvelenata.", 10, 10, Type::Poison));
    addMove(new DamageMove("Earthquake", "Scatena un terremoto distruttivo.", 40, 0, CharType::Knight));
    addMove(new DamageMove("Shadow Strike", "Attacca dall'oscurità con un colpo furtivo.", 20, 15, Type::Neutral));
    addMove(new DamageMove("Flame Slash", "Colpisce con una lama infuocata.", 18, 7, Type::Fire));
    addMove(new DamageMove("Thunder Shock", "Scaglia un fulmine scintillante.", 22, 10, Type::Air));
    addMove(new DamageMove("Venomous Bite", "Un morso con delle fauci velenose.", 14, 14, Type::Poison));
    addMove(new DamageMove("Boulder Toss", "Lancia massi giganti.", 45, 5, Type::Neutral));
    addMove(new DamageMove("Backstab", "Colpisce l'avversario alle spalle.", 25, 20, Type::Neutral));
    addMove(new DamageMove("Frostbite", "Congela l'avversario con il freddo.", 12, 18, Type::Air));
    addMove(new DamageMove("Toxic Cloud", "Rilascia una nuvola di veleno.", 10, 15, Type::Poison));
    addMove(new DamageMove("Lava Surge", "Scatena una colata di lava.", 35, 10, CharType::Dragon));
    addMove(new DamageMove("Charge", "Carica violentemente contro l'avversario.", 30, 5, CharType::Knight));
    addMove(new DamageMove("Sneak Attack", "Attacca furtivamente l'avversario alle spalle.", 28, 8, CharType::Goblin));
    addMove(new DamageMove("Meteor Strike", "Fai cadere un meteorite ardente sull'avversario.", 50, 5, CharType::Dragon));
    addMove(new DamageMove("Thunderstorm", "Scatena una tempesta di fulmini.", 40, 15, Type::Air));
    addMove(new DamageMove("Venomous Swipe", "Colpisce con una zampa velenosa.", 25, 20, Type::Poison));
    addMove(new DamageMove("Avalanche", "Scatena una valanga di massi.", 60, 5, CharType::Knight));
    addMove(new DamageMove("Critical Blow", "Esegue un colpo critico devastante.", 35, 30, Type::Neutral));
    addMove(new DamageMove("Frost Nova", "Genera un'esplosione di gelo.", 25, 20, Type::Air));
    addMove(new DamageMove("Acid Rain", "Fa piovere acido sul campo di battaglia.", 20, 25, Type::Poison));
    addMove(new DamageMove("Inferno", "Incendia tutto con un inferno ardente.", 55, 10, CharType::Dragon));
    addMove(new DamageMove("Charge", "Carica violentemente contro l'avversario.", 30, 5, CharType::Knight));
    addMove(new DamageMove("Assassinate", "Elimina l'avversario con un colpo mortale.", 40, 35, Type::Neutral));
    addMove(new DamageMove("Dragon Breath", "Soffia fuoco infuocato.", 40, 10, CharType::Dragon));
    addMove(new DamageMove("Wizard Blast", "Scatena un potente incantesimo magico.", 35, 15, CharType::Wizard));
    addMove(new DamageMove("Holy Smite", "Lancia un attacco divino.", 45, 5, CharType::Cleric));
    addMove(new DamageMove("Knight's Charge", "Carica con forza da cavaliere.", 30, 10, CharType::Knight));
    addMove(new DamageMove("Goblin Ambush", "Attacca di sorpresa da goblin.", 25, 15, CharType::Goblin));
    addMove(new DamageMove("Arcane Missile", "Scatena una pioggia di missili magici.", 20, 10, CharType::Wizard));
    addMove(new DamageMove("Lightning Bolt", "Lancia un fulmine devastante.", 30, 15, CharType::Wizard));
    addMove(new DamageMove("Abyss", "Crea una voragine nel terreno", 30,10,CharType::Boss));
    addMove(new DamageMove("God's tear", "Scatena una forza arcana", 25,25,CharType::Boss));



    // Mosse StatisticMove
    addMove(new StatisticMove("Physical Defense Buff", "Aumenta la difesa fisica a discapito dell'attacco magico.", {3, 0, 0, -2, 0}, Type::Earth, true));
    addMove(new StatisticMove("Speed Debuff", "Riduce la velocità dell'avversario.", {0, 0, 0, 0, 2}, Type::Neutral ,false));
    addMove(new StatisticMove("Magic Attack & Defense Buff", "Potenzia le statistiche magiche diminuendo però quelle fisiche.", {-3, 2, -2, 3, 0}, CharType::Cleric , true));
    addMove(new StatisticMove("Magic Attack Debuff", "Riduce l'attacco magico dell'avversario.", {4, 0, 0, 0, 0}, Type::Light , false));
    addMove(new StatisticMove("Magic Defense Buff", "Aumenta la difesa magica.", {0, 0, -3, 0, 0}, CharType::Cleric ,true));
    addMove(new StatisticMove("Physical Defense & Speed Buff", "Aumenta la difesa fisica e la velocità dell'utente.", {2, 0, 0, -2, -3}, Type::Neutral ,true));
    addMove(new StatisticMove("Life Points & Speed Debuff", "Riduce la velocità dell'avversario.", {0, 0, 0, 0, -3}, Type::Neutral ,false));
}


void MovesManager::addMove(Move* move){
    allMoves.push_back(move);
}

std::vector<Move*> MovesManager::getCompatibleMoves(const Character* ch) {
    std::vector<Move*> moves;
    for (const auto move : allMoves)
        if (move->isCompatible(ch))
            moves.push_back(move);

    return moves;
}

Move* MovesManager::moveByName(QString name) const{
    for(auto move : allMoves){
        if(move->getName()==name) return move;
    }
    return 0; // ERRORE DA TENERE D'OCCHIO
}
