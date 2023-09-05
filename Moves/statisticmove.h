#ifndef STATISTICMOVE_H
#define STATISTICMOVE_H

#include "move.h"

struct StatisticChanges {
    short magicAtkChange : 5,
            physicalAtkChange : 5,
            magicDefChange : 5,
            physicalDefChange : 5,
            speedChange : 5;
};


class StatisticMove : public Move
{
public:
    StatisticMove(QString, QString, StatisticChanges, Type);
    StatisticMove(QString, QString, StatisticChanges, CharType);
    void useMove(Character*, Character*) const override;

private:
    StatisticChanges changes;
};

#endif // STATISTICMOVE_H
