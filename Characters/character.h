#ifndef CHARACTER_H
#define CHARACTER_H

#include "Moves/move.h"
#include "type.h"

class Character
{
private:
    struct Statistics{
      // statistiche che devono assumere un valore da 0 a 10 eccetto la vita che arriva a massimo 100 nel caso del drago
      // (avendo a disposizione 12 bit ne abbiamo messi 11 per coprire future implementazioni di personaggi più forti)
      unsigned short magicAtk : 4,
          physicalAtk : 4,
          magicDef : 4,
          physicalDef : 4,
          speed : 4;
      unsigned short lifePoints : 11;
    };

    const unsigned short maxPS;
    bool abilityUsed;
    std::vector<Move*> moves;
    std::vector<Type> types;

    Statistics stats;
public:
    Character(unsigned short, unsigned short, unsigned short, unsigned short, unsigned short, unsigned short);

    virtual bool useAbility(Character*) = 0;

    unsigned short getPhyAtk() const;
    unsigned short getMagAtk() const;
    unsigned short getPhyDef() const;
    unsigned short getMagDef() const;
    unsigned short getLifePoints() const;
    unsigned short getSpeed() const;
    unsigned short getMaxPS() const;
    bool getAbilityUsed() const;

    void setPhyAtk(const unsigned short);
    void setMagAtk(const unsigned short);
    void setMagDef(const unsigned short);
    void setPhyDef(const unsigned short);
    void setSpeed(const unsigned short);
    void setAbilityUsed(const bool);
    virtual void setLifePoints(const unsigned short);
};

#endif // CHARACTER_H
