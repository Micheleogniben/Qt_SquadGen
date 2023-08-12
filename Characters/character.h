#ifndef CHARACTER_H
#define CHARACTER_H


class Character
{
private:
    struct Statistics{
      // statistiche che devono assumere un valore da 0 a 10
      unsigned short magicAtk : 4,
          physicalAtk : 4,
          magicDef : 4,
          physicalDef : 4,
          speed : 4;
      unsigned short lifePoints : 10;
    };

    const unsigned short maxPS;
    bool isDead;

    Statistics stats;
public:
    Character(unsigned short, unsigned short, unsigned short, unsigned short, unsigned short, unsigned short);

    virtual void useAbility(Character*) = 0;

    unsigned short getPhyAtk() const;
    unsigned short getMagAtk() const;
    unsigned short getPhyDef() const;
    unsigned short getMagDef() const;
    unsigned short getLifePoints() const;
    unsigned short getSpeed() const;
    unsigned short getMaxPS() const;

    void setPhyAtk(const unsigned short);
    void setMagAtk(const unsigned short);
    void setMagDef(const unsigned short);
    void setPhyDef(const unsigned short);
    void setSpeed(const unsigned short);
    virtual void setLifePoints(const unsigned short);
};

#endif // CHARACTER_H
