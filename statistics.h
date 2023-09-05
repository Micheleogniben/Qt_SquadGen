#ifndef STATISTICS_H
#define STATISTICS_H
#include "type.h"
#include <vector>

struct DefaultStats {
    unsigned short magAtk : 4,
                   phyAtk : 4,
                   magDef : 4,
                   phyDef : 4,
                   speed : 4,
                   weight : 9,
                   lifePts : 12;

    std::vector<Type> types;
    CharType charType;
};

// Dichiarazione delle variabili statiche globali per le statistiche dei personaggi
extern const DefaultStats dragonStats;
extern const DefaultStats clericStats;
extern const DefaultStats wizardStats;
extern const DefaultStats knightStats;
extern const DefaultStats goblinStats;

#endif // STATISTICS_H
