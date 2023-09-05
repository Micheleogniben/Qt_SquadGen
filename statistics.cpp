#include "statistics.h"

// Definizione delle variabili statiche globali per le statistiche dei personaggi
// Ordine: magAtk, phyAtk, magDef, phyDef, speed, weight, lifePts

const DefaultStats dragonStats = { 8,  8,  3,  8,  2, 30, 100, {Type::Fire,   Type::Air},     CharType::Dragon};
const DefaultStats clericStats = { 1,  1,  4,  1,  5,  9,  50, {Type::Light,  Type::Neutral}, CharType::Cleric};
const DefaultStats wizardStats = {10,  3, 10,  5,  7, 12,  75, {Type::Fire,   Type::Poison},  CharType::Wizard};
const DefaultStats knightStats = { 1, 10,  1, 10,  4, 15,  90, {Type::Earth,  Type::Neutral}, CharType::Knight};
const DefaultStats goblinStats = { 1,  4,  1,  2,  9,  2,  15, {Type::Poison, Type::Neutral}, CharType::Goblin};;
