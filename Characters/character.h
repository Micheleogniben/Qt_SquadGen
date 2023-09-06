#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>
#include "move.h"
#include "type.h"
#include "statistics.h"

class Character
{
private:
    struct Statistics{
      // statistiche che devono assumere un valore da 1 a 10 eccetto la vita che arriva a massimo 100 nel caso del drago,
        //  nel nostro caso per implementazioni future abbiamo deciso di rendere disponibili 12 bit (4095 vita max)
      unsigned short magicAtk : 4,
          physicalAtk : 4,
          magicDef : 4,
          physicalDef : 4,
          speed : 4,
          weight : 9,   // 9 bit mi permettono di arrivare a 511 di peso massimo, rendendo possibili implementazioni future
          lifePoints : 12;

      std::vector<Type> types;
      CharType charType;
    };

    const unsigned short maxPS;
    unsigned short burningTurns;
    bool abilityUsed;
    std::vector<const Move*> moves;
    QString name;
    Statistics stats;
public:
    Character(DefaultStats,QString);
    virtual ~Character();

    virtual bool useAbility(Character*) = 0;
    void addMove(const Move*);

    unsigned short getPhyAtk() const;
    unsigned short getMagAtk() const;
    unsigned short getPhyDef() const;
    unsigned short getMagDef() const;
    unsigned short getLifePoints() const;
    unsigned short getSpeed() const;
    unsigned short getWeight() const;
    unsigned short getMaxPS() const;
    unsigned short getBurnign() const;
    bool getAbilityUsed() const;
    std::vector<Type> getTypes() const;
    CharType getCharType() const;
    QString getName() const;
    QString getMovesNames() const;

    void setPhyAtk(const unsigned short);
    void setMagAtk(const unsigned short);
    void setMagDef(const unsigned short);
    void setPhyDef(const unsigned short);
    void setSpeed(const unsigned short);
    void setBurning(const unsigned short);
    void setAbilityUsed(const bool);
    virtual void setLifePoints(const unsigned short);
    void clearMoves();
};

#endif // CHARACTER_H
