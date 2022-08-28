#include <iostream>
#include <vector>

using namespace std;

class Skill
{
protected:

    Skill()
    = default;
};

class Stun_Skill
{
protected:
    int stunBase;
public:
    virtual int getStunBase()
    {
        return stunBase;
    }
};

class Attack : public Skill
{
protected:
    double dmgMod;
    double baseAcc;
    double critMod;

public:
    virtual double getBaseAcc()
    {
        return baseAcc;
    }

    virtual double getDmgMod()
    {
        return dmgMod;
    }

    virtual double getCritMod()
    {
        return critMod;
    }

    virtual double UseAttack(vector<Hero> Heroes, int unitPos)
    {
        int minDmg = Heroes[unitPos - 1].getMinDmg();
        int maxDmg = Heroes[unitPos - 1].getMaxDmg();

        double baseCrit = Heroes[unitPos - 1].getBaseCrit();
        double critChance = baseCrit + critMod;

        int rngJesusCrit = (rand() % 101);

        double dmg;

        if(rngJesusCrit <= critChance)
        {
            dmg = 1.5 * Heroes[unitPos - 1].getMaxDmg();

        } else
        {
            dmg = (rand() % (maxDmg - minDmg) + minDmg);
        }

        double rawDmg = dmg * (100 + dmgMod) / 100;

        return rawDmg;
    }

    virtual double UseMonsterAttack(vector<Monster> BoneSquad, int unitPos)
    {
        int minDmg = BoneSquad[unitPos - 1].getMinDmg();
        int maxDmg = BoneSquad[unitPos - 1].getMaxDmg();

        double baseCrit = BoneSquad[unitPos - 1].getBaseCrit();
        double critChance = baseCrit + critMod;

        int rngJesusCrit = (rand() % 101);

        double dmg;

        if(rngJesusCrit <= critChance)
        {
            dmg = 1.5 * BoneSquad[unitPos - 1].getMaxDmg();

        } else
        {
            dmg = (rand() % (maxDmg - minDmg) + minDmg);
        }

        double rawDmg = dmg * (100 + dmgMod) / 100;

        return rawDmg;
    }
};

class Utility : public Skill
{
protected:
    int minHeal;
    int maxHeal;
    int roundTime;
    int protectionBuff;
public:
    template <class T>
    void healAll(vector<T> & Group)
    {
        int rngJesusHeal = (rand() % (maxHeal - minHeal)) + minHeal;
        for(int i = 0; i < 4; i++)
        {
            Group[i].heal(rngJesusHeal);
        }
        cout << "All units healed " << rngJesusHeal << " health points." << endl;
    }

    template <class T>
    void healTarget(vector<T> & Group, int targetPos)
    {
        int rngJesusHeal = (rand() % (maxHeal - minHeal)) + minHeal;
        Group[targetPos - 1].heal(rngJesusHeal);
        cout << "Teammate healed " << rngJesusHeal << " health points." << endl;
    }

    template <class T>
    void protBuff(vector<T> & Group, int targetPos)
    {
        Group[targetPos - 1].setBuffRate(protectionBuff);
        Group[targetPos - 1].setBuffDur(roundTime);
        cout << Group[targetPos - 1].getName() << " gained +" << protectionBuff << " protection for " << roundTime << " rounds." << endl;
    }
};

class Move : public Skill
{
public:
    template <class T>
    vector<T> unitSwapMove(int currentPos, int newPos, vector<T> &Vector)
    {
        swap(Vector[currentPos - 1], Vector[newPos - 1]);
        return Vector;
    }

    template <class T>
    vector<T> unitForwardMove(int currentPos, vector<T> &Vector)
    {
        if(currentPos > 1)
        {
            swap(Vector[currentPos - 1], Vector[currentPos - 2]);
            return Vector;
        } else
        {
            cout << "Unit is already at the frontline." << endl;
            return Vector;
        }
    }

    template <class T>
    vector<T> unitBackwardMove(int currentPos, vector<T> &Vector)
    {
        if(currentPos < 4)
        {
            swap(Vector[currentPos - 1], Vector[currentPos]);
            return Vector;
        } else{
            cout << "Unit is already at the backline." << endl;
        }
    }
};

class Smite : public Attack
{
public:
    Smite()
    {
        dmgMod = 0;
        baseAcc = 85;
        critMod = 0;
    }
};

class Stunning_Blow : public Attack, public Stun_Skill
{
public:
    Stunning_Blow()
    {
        dmgMod = -50;
        baseAcc = 90;
        critMod = 0;
        stunBase = 100;
    }
};

class Holy_Lance : public Attack, public Move
{
public:
    Holy_Lance()
    {
        dmgMod = 0;
        baseAcc = 85;
        critMod = 6.5;
    }
};

class Bulwark : public Utility
{
public:
    Bulwark()
    {
        protectionBuff = 20;
        roundTime = 3;
    }
};

class Mace_Bash : public Attack
{
public:
    Mace_Bash()
    {
        dmgMod = 0;
        baseAcc = 85;
        critMod = 0;
    }
};

class Dazzling_Light : public Attack, public Stun_Skill
{
public:
    Dazzling_Light()
    {
        dmgMod = -75;
        baseAcc = 90;
        critMod = 5;
        stunBase = 100;
    }
};

class Divine_Grace : public Utility
{
public:
    Divine_Grace()
    {
        minHeal = 4;
        maxHeal = 5;
    }
};

class Divine_Comfort : public Utility
{
public:
    Divine_Comfort()
    {
        minHeal = 1;
        maxHeal = 3;
    }
};

class Graveyard_Slash : public Attack
{
public:
    Graveyard_Slash()
    {
        dmgMod = 0;
        baseAcc = 85;
        critMod = 6;
    }
};

class Graveyard_Stumble : public Attack, public Move
{
public:
    Graveyard_Stumble()
    {
        dmgMod = -50;
        baseAcc = 45;
        critMod = 0;
    }
};

class Axeblade : public Attack
{
public:
    Axeblade()
    {
        dmgMod = 0;
        baseAcc = 72;
        critMod = 6;
    }
};

class Dead_Weight : public Attack, public Stun_Skill
{
public:
    Dead_Weight()
    {
        dmgMod = -25;
        baseAcc = 82;
        critMod = 6;
        stunBase = 100;
    }
};

class Knitting_Bones : public Utility
{
public:
    Knitting_Bones()
    {
        minHeal = 2;
        maxHeal = 3;
    }
};
