#include <iostream>

using namespace std;

class Unit
{
protected:
    string Name;
    string Class;

    int max_HP;
    int healthPoint;

    double dodge;
    double protection;
    int speed;

    bool isStunned = false;
    int buffDur;
    int buffRate = 0;

    double accMod;
    double baseCrit;
    int minDmg;
    int maxDmg;
    double stunRes;
    int deathBlowRes = 0;
public:


    Unit()
    {
    }

    void inflictDMG(int incomingDMG)
    {
        if(healthPoint >= incomingDMG)
        {
            healthPoint -= incomingDMG;
        } else
        {
            healthPoint = 0;
        }
    }

    virtual void heal(int amount)
    {
        if(amount + healthPoint < max_HP)
        {
            healthPoint += amount;
        }
        else
        {
            healthPoint = max_HP;
        }
    }

    virtual int getBuffDur()
    {
        return buffDur;
    }

    virtual void decreaseDur()
    {
        if(buffDur > 0)
        {
            buffDur--;
        }
    }

    virtual void setBuffRate(int rate)
    {
        buffRate = rate;
    }

    virtual void setBuffDur(int time)
    {
        buffDur = time;
    }

    virtual bool getStunned()
    {
        return isStunned;
    }

    virtual void setStun()
    {
        isStunned = true;
    }

    virtual void deStun()
    {
        isStunned = false;
    }

    virtual void setDead()
    {
        speed = -1000;
        Name = "Dead";
        max_HP = 0;
        healthPoint = -1;
    }

    int getSpeed()
    {
        return speed;
    }

    virtual string getName()
    {
        return Name;
    }

    virtual string getClass()
    {
        return Class;
    }

    virtual double getMinDmg()
    {
        return minDmg;
    }

    virtual double getMaxDmg()
    {
        return maxDmg;
    }

    virtual double getAccMod()
    {
        return accMod;
    }

    virtual double getBaseCrit()
    {
        return baseCrit;
    }

    virtual double getStunRes()
    {
        return stunRes;
    }

    virtual double getDodge()
    {
        return dodge;
    }

    virtual double getProt()
    {
        return protection;
    }

    virtual int getMaxHP()
    {
        return max_HP;
    }

    virtual int getHP()
    {
        return healthPoint;
    }

    virtual int getDeathRes()
    {
        return 0;
    }
};

class Hero : public Unit
{
protected:
    int deathBlowRes;
public:
    int getDeathRes()
    {
        return deathBlowRes;
    }

    double getProt()
    {
        return protection + buffRate;
    }
};

class Monster : public Unit
{
};

class Vestal : public Hero
{
public:
    Vestal(string name)
    {
        Name = name;
        Class = "Vestal";

        max_HP = 24;
        healthPoint = 24;

        dodge = 0;
        protection = 0;
        speed = 4;
        accMod = 0;
        baseCrit = 1;
        minDmg = 4;
        maxDmg = 8;
        deathBlowRes = 77;
        stunRes = 30;
    }
};

class Crusader : public Hero
{
public:
    Crusader(string name)
    {
        Name = name;
        Class = "Crusader";

        max_HP = 35;
        healthPoint = 35;

        dodge = 5;
        protection = 0;
        buffRate = 0;
        buffDur = 0;
        speed = 1;
        accMod = 0;
        baseCrit = 3;
        minDmg = 6;
        maxDmg = 12;
        deathBlowRes = 67;
        stunRes = 40;
    }

    virtual double getProt()
    {
        return protection + buffRate;
    }

    virtual void inflictDMG(int incomingDMG)
    {
        if(healthPoint >= incomingDMG)
        {
            healthPoint -= incomingDMG;
        } else
        {
            healthPoint = 0;
        }
    }
};

class Bone_Soldier : public Monster
{
public:
    Bone_Soldier(string name)
    {
        Name = name;
        Class = "BoneSoldier";

        max_HP = 10;
        healthPoint = 10;

        dodge = 10;
        protection = 15;
        speed = 2;
        accMod = 0;
        baseCrit = 0;
        minDmg = 3;
        maxDmg = 8;
        stunRes = 25;
    }

};

class Bone_Defender : public Monster
{
public:
    Bone_Defender(string name)
    {
        Name = name;
        Class = "BoneDefender";

        max_HP = 22;
        healthPoint = 22;

        dodge = 8;
        protection = 45;
        speed = 1;
        accMod = 0;
        baseCrit = 0;
        minDmg = 2;
        maxDmg = 4;
        stunRes = 45;
    }

};
