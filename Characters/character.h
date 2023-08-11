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
      unsigned short lifePoints;
    };

    Statistics stats;
public:
    Character();
    Character(unsigned short, unsigned short, unsigned short, unsigned short, unsigned short, unsigned short);

    virtual void useAbility(Character*) = 0;

    unsigned short getPhyAtk();
    unsigned short getMagAtk();
    unsigned short getPhyDef();
    unsigned short getMagDef();
    unsigned short getLifePoints();

    void setPhyAtk(unsigned short);
    void setMagAtk(unsigned short);
    void setMagDef(unsigned short);
    void setPhyDef(unsigned short);
    void setLifePoints(unsigned short);
};

#endif // CHARACTER_H
