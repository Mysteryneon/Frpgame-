#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>

#include "Units.h"
#include "Skills.h"

using namespace std;


int unitPosition(vector<Hero> heroVector, vector<Monster> monsterVector, string neededUnit)
{
    int position;
    for(int i = 0; i < 4; i++)
    {
        if (heroVector[i].getName() == neededUnit)
        {
            position = i + 1;
            break;
        }
    }
    for(int i = 4; i < 8; i++)
    {
        if(monsterVector[i - 4].getName() == neededUnit)
        {
            position = i + 1;
            break;
        }
    }
    return position;
}

template <class T>

void AttackAction(T & Target, double rawDMG, vector<T>  & targetsGroup)
{
    int targetHP = Target.getHP();
    double prot = Target.getProt();
    double actualDMGDoub = rawDMG - rawDMG*(prot/100);

    int actualDMG = int(actualDMGDoub);

    if(targetHP == 0)
    {
        int deathRes = Target.getDeathRes();
        int reaper = (rand() % 101);

        if(reaper <= deathRes)
        {
            cout << Target.getName() << " still holds on to life." << endl;
        } else{
            cout << Target.getName() << " is dead." << endl;
            Target.setDead();

        }

    } else {
        if(actualDMG < targetHP)
        {
            Target.inflictDMG(actualDMG);
            cout << Target.getName() << " received " << actualDMG << " damage." << endl;
        } else {
            string targetClass = Target.getClass();
            if (targetClass == "Vestal" or targetClass == "Crusader") {
                Target.inflictDMG(targetHP);
                cout << Target.getName() << " at Death's Door!" << endl;
            } else
            {
                Target.setDead();
                cout << Target.getName() << " is dead.";
            }
        }
    }
}

int main() {

    Vestal Vestal1("Kairi");
    Vestal Vestal2("Elsa");
    Crusader Crusader1("Ezio");
    Crusader Crusader2("Geralt");

    Smite Smite;
    Stunning_Blow StunningBlow;
    Holy_Lance HolyLance;
    Bulwark Bulwark;

    Mace_Bash MaceBash;
    Dazzling_Light DazzLight;
    Divine_Grace Grace;
    Divine_Comfort Comfort;

    Bone_Defender Defender1("Sam");
    Bone_Defender Defender2("LivingTombstone");
    Bone_Soldier Soldier1("Grave Digger");
    Bone_Soldier Soldier2("Lich King");

    Graveyard_Slash GrSlash;
    Graveyard_Stumble GrStumble;

    Axeblade Axeblade;
    Dead_Weight DeadWeight;
    Knitting_Bones KnitBones;
    Move Move;

    vector<Hero> Heroes = {Crusader1, Crusader2, Vestal1, Vestal2};
    vector<Monster> BoneSquad = {Soldier1, Defender1, Soldier2, Defender2};

    cout << "Game Booted" << endl;

    int roundCount = 1;
    srand((unsigned)time(0));

    bool isGameOverHeroesWin = false;
    bool isGameOverMonstersWin = false;

    while(true)
    {
        cout << "Start of Round " << roundCount << endl;

        int turnTable[8];
        string unitIndex[8] ={Crusader1.getName(), Crusader2.getName(), Vestal1.getName(), Vestal2.getName(),
                              Soldier1.getName(),Defender1.getName(), Soldier2.getName(), Defender2.getName()};

        int turnIndex = 0;

        for(int i = 0; i < 4; i++)
        {
            int speedRNG = (rand() % 8) + 1;
            int unitSpeed = Heroes[i].getSpeed();

            int speed = speedRNG + unitSpeed;

            turnTable[turnIndex] = speed;
            turnIndex++;
        }

        for(int i = 0; i < 4; i++)
        {
            int speedRNG = (rand() % 8) + 1;
            int unitSpeed = BoneSquad[i].getSpeed();

            int speed = speedRNG + unitSpeed;

            turnTable[turnIndex] = speed;
            turnIndex++;
        }

        for(int i = 0; i < 7; i++)
        {
            for(int j = i + 1; j < 8; j++)
            {
                if(turnTable[j] > turnTable[i])
                {
                    int speedKey = turnTable[j];
                    string unitKey = unitIndex[j];

                    turnTable[j] = turnTable[i];
                    unitIndex[j] = unitIndex[i];

                    turnTable[i] = speedKey;
                    unitIndex[i] = unitKey;
                }
            }
        }

        for(int i = 0; i < 8; i++)
        {
            if(turnTable[i] >= 0)
            {
                cin.ignore();
                cout << endl;
                cout << unitIndex[i] << "'s Turn" << endl;

                string unitName = unitIndex[i];
                int unitPos = unitPosition(Heroes, BoneSquad, unitName);
                string classType;
                int maxHealth, currentHealth;
                bool isStunned = false;

                if(unitPos <= 4)
                {
                    classType = Heroes[unitPos - 1].getClass();
                    maxHealth = Heroes[unitPos - 1].getMaxHP();
                    currentHealth = Heroes[unitPos - 1].getHP();
                    isStunned = Heroes[unitPos - 1].getStunned();
                    Heroes[unitPos - 1].deStun();
                    if(Heroes[unitPos - 1].getBuffDur() > 0)
                    {
                        Heroes[unitPos - 1].decreaseDur();
                    } else{
                        Heroes[unitPos - 1].setBuffRate(0);
                    }
                }
                else
                {
                    unitPos -= 4;
                    classType = BoneSquad[unitPos - 1].getClass();
                    maxHealth = BoneSquad[unitPos - 1].getMaxHP();
                    currentHealth = BoneSquad[unitPos - 1].getHP();
                    isStunned = BoneSquad[unitPos - 1].getStunned();
                    BoneSquad[unitPos - 1].deStun();
                    if(BoneSquad[unitPos - 1].getBuffDur() > 0)
                    {
                        BoneSquad[unitPos - 1].decreaseDur();
                    } else{
                        BoneSquad[unitPos - 1].setBuffRate(0);
                    }
                }

                cout << "Position: " << unitPos << " Class: " << classType << endl;
                cout << "HP: " <<  currentHealth << "/" << maxHealth << endl;

                if(isStunned)
                {
                    cout << unitName << " is stunned! Turn Passed." << endl;
                } else
                {


                    if(classType == "Vestal")
                    {
                        double modAcc = Heroes[unitPos - 1].getAccMod();
                        cout << "Available Actions:" << endl;
                        int selectedAction = 0;

                        if(unitPos == 1)
                        {
                            cout << "1 - Mace Bash" << endl;
                            cout << "2 - Move" << endl;
                            cout << "3 - Rest" << endl;

                            while(true)
                            {
                                cin >> selectedAction;
                                if(selectedAction == 1 or selectedAction == 2 or selectedAction == 3)
                                {
                                    break;
                                } else{
                                    cout << "This action is not allowed." << endl;
                                }
                            }

                            int selectedTarget;

                            if(selectedAction == 1)
                            {
                                cout << "Select Your Target: " << endl;
                                cout << "1- " << BoneSquad[0].getName() << " " << BoneSquad[0].getHP() << "/" << BoneSquad[0].getMaxHP() << endl;
                                cout << "2- " << BoneSquad[1].getName() << " " << BoneSquad[1].getHP() << "/" << BoneSquad[1].getMaxHP() << endl;

                                while(true)
                                {
                                    cin >> selectedTarget;
                                    if(selectedTarget == 1 or selectedTarget == 2)
                                    {
                                        break;
                                    } else
                                    {
                                        cout << "Invalid Target." << endl;
                                    }
                                }

                                cout << Heroes[unitPos - 1].getName() << " tries to use Mace Bash against " << BoneSquad[selectedTarget - 1].getName() << endl;
                                double baseAcc = MaceBash.getBaseAcc();
                                double dodgeTarget = BoneSquad[selectedTarget - 1].getDodge();
                                double hitChance = baseAcc + modAcc - dodgeTarget;

                                int rngJesusHit = (rand() % 101);

                                if(rngJesusHit <= hitChance)
                                {
                                    double rawDmg = MaceBash.UseAttack(Heroes, unitPos);

                                    AttackAction(BoneSquad[selectedTarget - 1], rawDmg, BoneSquad);

                                } else{
                                    cout << "Attack Missed!" << endl;
                                }
                            }
                            else if(selectedAction == 3)
                            {
                                cout << unitIndex[i] << " rests for this turn." << endl;
                            }
                            else if(selectedAction == 2)
                            {
                                cout << "Choose new position: " << endl;
                                int newPos;
                                cin >> newPos;
                                vector<Hero> Mover = Move.unitSwapMove(unitPos, newPos, Heroes);
                                Heroes.swap(Mover);
                            }

                        }
                        else if(unitPos == 2)
                        {
                            cout << "1 - Mace Bash" << endl;
                            cout << "2 - Dazzling Light" << endl;
                            cout << "3 - Divine Comfort" << endl;
                            cout << "4 - Move" << endl;
                            cout << "5 - Rest" << endl;

                            while(true)
                            {
                                cin >> selectedAction;
                                if(selectedAction == 1 or selectedAction == 2 or
                                   selectedAction == 3 or selectedAction == 4 or selectedAction == 5)
                                {
                                    break;
                                } else{
                                    cout << "This action is not allowed." << endl;
                                }
                            }

                            int selectedTarget;

                            if(selectedAction == 1)
                            {
                                cout << "Select Your Target: " << endl;
                                cout << "1- " << BoneSquad[0].getName() << " " << BoneSquad[0].getHP() << "/" << BoneSquad[0].getMaxHP() << endl;
                                cout << "2- " << BoneSquad[1].getName() << " " << BoneSquad[1].getHP() << "/" << BoneSquad[1].getMaxHP() << endl;

                                while(true)
                                {
                                    cin >> selectedTarget;
                                    if(selectedTarget == 1 or selectedTarget == 2)
                                    {
                                        break;
                                    } else
                                    {
                                        cout << "Invalid Target." << endl;
                                    }
                                }

                                cout << Heroes[unitPos - 1].getName() << " tries to use Mace Bash against " << BoneSquad[selectedTarget - 1].getName() << endl;

                                double baseAcc = MaceBash.getBaseAcc();
                                double dodgeTarget = BoneSquad[selectedTarget - 1].getDodge();
                                double hitChance = baseAcc + modAcc - dodgeTarget;

                                int rngJesusHit = (rand() % 101);

                                if(rngJesusHit <= hitChance)
                                {
                                    double rawDmg = MaceBash.UseAttack(Heroes, unitPos);

                                    AttackAction(BoneSquad[selectedTarget - 1], rawDmg, BoneSquad);

                                } else{
                                    cout << "Attack Missed!" << endl;
                                }
                            }
                            else if(selectedAction == 2)
                            {
                                cout << "Select Your Target: " << endl;
                                cout << "1- " << BoneSquad[0].getName() << " " << BoneSquad[0].getHP() << "/" << BoneSquad[0].getMaxHP() << endl;
                                cout << "2- " << BoneSquad[1].getName() << " " << BoneSquad[1].getHP() << "/" << BoneSquad[1].getMaxHP() << endl;
                                cout << "3- " << BoneSquad[2].getName() << " " << BoneSquad[2].getHP() << "/" << BoneSquad[2].getMaxHP() << endl;

                                while(true)
                                {
                                    cin >> selectedTarget;
                                    if(selectedTarget == 1 or selectedTarget == 2 or selectedTarget == 3)
                                    {
                                        break;
                                    } else
                                    {
                                        cout << "Invalid Target." << endl;
                                    }
                                }

                                cout << Heroes[unitPos - 1].getName() << " tries to use Dazzling Light against " << BoneSquad[selectedTarget - 1].getName() << endl;

                                double baseAcc = DazzLight.getBaseAcc();
                                double dodgeTarget = BoneSquad[selectedTarget - 1].getDodge();
                                double hitChance = baseAcc + modAcc - dodgeTarget;

                                int rngJesusHit = (rand() % 101);

                                if(rngJesusHit <= hitChance)
                                {
                                    int stunChance = DazzLight.getStunBase() - BoneSquad[selectedTarget - 1].getStunRes();
                                    double rawDmg = DazzLight.UseAttack(Heroes, unitPos);

                                    if(rawDmg / 1.5 == Heroes[unitPos - 1].getMaxDmg())
                                    {
                                        stunChance += 20;
                                    }

                                    int rngJesusStun = (rand() % 101);
                                    if(rngJesusStun <= stunChance)
                                    {
                                        BoneSquad[selectedTarget - 1].setStun();
                                        cout << "Target Stunned!" << endl;
                                    } else{
                                        cout << "Stun failed." << endl;
                                    }

                                }else
                                {
                                    cout << "Attack Missed!" << endl;
                                }
                            }
                            else if(selectedAction == 3)
                            {
                                cout << Heroes[unitPos - 1].getName() << " heals the team." << endl;
                                Comfort.healAll(Heroes);
                            }
                            else if(selectedAction == 5)
                            {
                                cout << unitIndex[i] << " rests for this turn." << endl;
                            }
                            else if(selectedAction == 4)
                            {
                                cout << "Choose new position: " << endl;
                                int newPos;
                                cin >> newPos;
                                vector<Hero> Mover = Move.unitSwapMove(unitPos, newPos, Heroes);
                                Heroes.swap(Mover);
                            }
                        }
                        else if(unitPos == 3 or unitPos == 4)
                        {
                            cout << "1 - Divine Grace" << endl;
                            cout << "2 - Dazzling Light" << endl;
                            cout << "3 - Divine Comfort" << endl;
                            cout << "4 - Move" << endl;
                            cout << "5 - Rest" << endl;

                            while(true)
                            {
                                cin >> selectedAction;
                                if(selectedAction == 1 or selectedAction == 2 or
                                   selectedAction == 3 or selectedAction == 4 or selectedAction == 5)
                                {
                                    break;
                                } else{
                                    cout << "This action is not allowed." << endl;
                                }
                            }

                            int selectedTarget;

                            if(selectedAction == 1)
                            {
                                cout << "Select a Teammate to Heal: " << endl;
                                cout << "1- " << Heroes[0].getName() << Heroes[0].getHP() << "/" << Heroes[0].getMaxHP() << endl;
                                cout << "2- " << Heroes[1].getName() << Heroes[1].getHP() << "/" << Heroes[1].getMaxHP() << endl;
                                cout << "3- " << Heroes[2].getName() << Heroes[2].getHP() << "/" << Heroes[2].getMaxHP() << endl;
                                cout << "4- " << Heroes[3].getName() << Heroes[3].getHP() << "/" << Heroes[3].getMaxHP() << endl;

                                while(true)
                                {
                                    cin >> selectedTarget;
                                    if(selectedTarget == 1 or selectedTarget == 2 or selectedTarget == 3 or selectedTarget == 4)
                                    {
                                        break;
                                    } else
                                    {
                                        cout << "Invalid Target." << endl;
                                    }
                                }

                                cout << Heroes[unitPos - 1].getName() << " heals " << Heroes[selectedTarget - 1].getName() << endl;
                                Grace.healTarget(Heroes, selectedTarget);
                            }
                            else if(selectedAction == 2)
                            {
                                cout << "Select Your Target: " << endl;
                                cout << "1- " << BoneSquad[0].getName() << " " << BoneSquad[0].getHP() << "/" << BoneSquad[0].getMaxHP() << endl;
                                cout << "2- " << BoneSquad[1].getName() << " " << BoneSquad[1].getHP() << "/" << BoneSquad[1].getMaxHP() << endl;
                                cout << "3- " << BoneSquad[2].getName() << " " << BoneSquad[2].getHP() << "/" << BoneSquad[2].getMaxHP() << endl;

                                while(true)
                                {
                                    cin >> selectedTarget;
                                    if(selectedTarget == 1 or selectedTarget == 2 or selectedTarget == 3)
                                    {
                                        break;
                                    } else
                                    {
                                        cout << "Invalid Target." << endl;
                                    }
                                }

                                cout << Heroes[unitPos - 1].getName() << " tries to use Dazzling Light against " << BoneSquad[selectedTarget - 1].getName() << endl;

                                double baseAcc = DazzLight.getBaseAcc();
                                double dodgeTarget = BoneSquad[selectedTarget - 1].getDodge();
                                double hitChance = baseAcc + modAcc - dodgeTarget;

                                int rngJesusHit = (rand() % 101);

                                if(rngJesusHit <= hitChance)
                                {
                                    int stunChance = DazzLight.getStunBase() - BoneSquad[selectedTarget - 1].getStunRes();
                                    double rawDmg = DazzLight.UseAttack(Heroes, unitPos);

                                    if(rawDmg / 1.5 == Heroes[unitPos - 1].getMaxDmg())
                                    {
                                        stunChance += 20;
                                    }

                                    int rngJesusStun = (rand() % 101);
                                    if(rngJesusStun <= stunChance)
                                    {
                                        BoneSquad[selectedTarget - 1].setStun();
                                        cout << "Target Stunned!" << endl;
                                    } else{
                                        cout << "Stun failed." << endl;
                                    }

                                }else
                                {
                                    cout << "Attack Missed!" << endl;
                                }



                            }
                            else if(selectedAction == 3)
                            {
                                cout << Heroes[unitPos - 1].getName() << " heals the team." << endl;
                                Comfort.healAll(Heroes);
                            }
                            else if(selectedAction == 5)
                            {
                                cout << unitIndex[i] << " rests for this turn." << endl;
                            }
                            else if(selectedAction == 4)
                            {
                                cout << "Choose new position: " << endl;
                                int newPos;
                                cin >> newPos;
                                vector<Hero> Mover = Move.unitSwapMove(unitPos, newPos, Heroes);
                                Heroes.swap(Mover);
                            }
                        };
                    }
                    else if(classType == "Crusader")
                    {
                        double modAcc = Heroes[unitPos - 1].getAccMod();

                        cout << "Available Actions:" << endl;
                        int selectedAction = 0;

                        if(unitPos == 1 or unitPos == 2)
                        {
                            cout << "1 - Smite" << endl;
                            cout << "2 - Stunning Blow" << endl;
                            cout << "3 - Bulwark of Faith" << endl;
                            cout << "4 - Move" << endl;
                            cout << "5 - Rest" << endl;

                            while(true)
                            {
                                cin >> selectedAction;
                                if(selectedAction == 1 or selectedAction == 2 or
                                   selectedAction == 3 or selectedAction == 4 or selectedAction == 5)
                                {
                                    break;
                                } else{
                                    cout << "This action is not allowed." << endl;
                                }
                            }

                            int selectedTarget = 0;

                            if(selectedAction == 1) //Smite
                            {
                                cout << "Select Your Target: " << endl;
                                cout << "1- " << BoneSquad[0].getName() << " " << BoneSquad[0].getHP() << "/" << BoneSquad[0].getMaxHP() << endl;
                                cout << "2- " << BoneSquad[1].getName() << " " << BoneSquad[1].getHP() << "/" << BoneSquad[1].getMaxHP() << endl;

                                while(true)
                                {
                                    cin >> selectedTarget;
                                    if(selectedTarget == 1 or selectedTarget == 2)
                                    {
                                        break;
                                    } else
                                    {
                                        cout << "Invalid Target." << endl;
                                    }
                                }

                                cout << Heroes[unitPos - 1].getName() << " tries to use Smite against " << BoneSquad[selectedTarget - 1].getName() << endl;

                                double baseAcc = Smite.getBaseAcc();
                                double dodgeTarget = BoneSquad[selectedTarget - 1].getDodge();
                                double hitChance = baseAcc + modAcc - dodgeTarget;

                                int rngJesusHit = (rand() % 101);

                                if(rngJesusHit <= hitChance)
                                {
                                    double rawDmg = MaceBash.UseAttack(Heroes, unitPos);

                                    AttackAction(BoneSquad[selectedTarget - 1], rawDmg, BoneSquad);

                                } else{
                                    cout << "Attack Missed!" << endl;
                                }
                            }
                            else if(selectedAction == 2) //StunningBlow
                            {
                                cout << "Select Your Target: " << endl;
                                cout << "1- " << BoneSquad[0].getName() << " " << BoneSquad[0].getHP() << "/" << BoneSquad[0].getMaxHP() << endl;
                                cout << "2- " << BoneSquad[1].getName() << " " << BoneSquad[1].getHP() << "/" << BoneSquad[1].getMaxHP() << endl;

                                while(true)
                                {
                                    cin >> selectedTarget;
                                    if(selectedTarget == 1 or selectedTarget == 2)
                                    {
                                        break;
                                    } else
                                    {
                                        cout << "Invalid Target." << endl;
                                    }
                                }

                                cout << Heroes[unitPos - 1].getName() << " tries to use Stunning Blow against " << BoneSquad[selectedTarget - 1].getName() << endl;

                                double baseAcc = StunningBlow.getBaseAcc();
                                double dodgeTarget = BoneSquad[selectedTarget - 1].getDodge();
                                double hitChance = baseAcc + modAcc - dodgeTarget;

                                int rngJesusHit = (rand() % 101);

                                if(rngJesusHit <= hitChance)
                                {
                                    double rawDmg = StunningBlow.UseAttack(Heroes, unitPos);
                                    int stunChance = StunningBlow.getStunBase() - BoneSquad[selectedTarget - 1].getStunRes();

                                    if(rawDmg / 1.5 == Heroes[unitPos - 1].getMaxDmg())
                                    {
                                        stunChance += 20;
                                    }

                                    int rngJesusStun = (rand() % 101);
                                    if(rngJesusStun <= stunChance)
                                    {
                                        BoneSquad[selectedTarget - 1].setStun();
                                        cout << "Target Stunned!" << endl;
                                    } else{
                                        cout << "Stun failed." << endl;
                                    }

                                    AttackAction(BoneSquad[selectedTarget - 1], rawDmg, BoneSquad);
                                } else{
                                    cout << "Attack Missed!" << endl;
                                }

                            }
                            else if(selectedAction == 3) //BulwarkofFaith
                            {
                                cout << Heroes[unitPos - 1].getName() << " buffs itself." << endl;
                                Bulwark.protBuff(Heroes, unitPos);
                            }
                            else if(selectedAction == 4)
                            {
                                cout << "Choose new position: " << endl;
                                int newPos;
                                cin >> newPos;
                                vector<Hero> Mover = Move.unitSwapMove(unitPos, newPos, Heroes);
                                Heroes.swap(Mover);
                            }
                            else if(selectedAction == 5)
                            {
                                cout << unitIndex[i] << " rests for this turn." << endl;
                            }
                        }
                        else if(unitPos == 3 or unitPos == 4)
                        {
                            cout << "1 - Holy Lance" << endl;
                            cout << "2 - Move" << endl;
                            cout << "3 - Rest" << endl;

                            while(true)
                            {
                                cin >> selectedAction;
                                if(selectedAction == 1 or selectedAction == 2 or selectedAction == 3)
                                {
                                    break;
                                } else{
                                    cout << "This action is not allowed." << endl;
                                }
                            }

                            int selectedTarget = 0;

                            if(selectedAction == 1)
                            {
                                cout << "Select Your Target: " << endl;
                                cout << "1- " << BoneSquad[1].getName() << " " << BoneSquad[1].getHP() << "/" << BoneSquad[1].getMaxHP() << endl;
                                cout << "2- " << BoneSquad[2].getName() << " " << BoneSquad[2].getHP() << "/" << BoneSquad[2].getMaxHP() << endl;
                                cout << "3- " << BoneSquad[3].getName() << " " << BoneSquad[3].getHP() << "/" << BoneSquad[3].getMaxHP() << endl;

                                while(true)
                                {
                                    cin >> selectedTarget;
                                    if(selectedTarget == 1 or selectedTarget == 2 or selectedTarget == 3)
                                    {
                                        break;
                                    } else
                                    {
                                        cout << "Invalid Target." << endl;
                                    }
                                }

                                cout << Heroes[unitPos - 1].getName() << " tries to use Holy Lance against " << BoneSquad[selectedTarget - 1].getName() << endl;

                                double baseAcc = HolyLance.getBaseAcc();
                                double dodgeTarget = BoneSquad[selectedTarget - 1].getDodge();
                                double hitChance = baseAcc + modAcc - dodgeTarget;

                                int rngJesusHit = (rand() % 101);

                                if(rngJesusHit <= hitChance)
                                {
                                    double rawDmg = HolyLance.UseAttack(Heroes, unitPos);

                                    AttackAction(BoneSquad[selectedTarget - 1], rawDmg, BoneSquad);

                                    vector<Hero> Mover = Move.unitForwardMove(unitPos, Heroes);
                                    Heroes.swap(Mover);

                                } else{
                                    cout << "Attack Missed!" << endl;
                                }
                            }
                            else if(selectedAction == 2)
                            {
                                cout << "Choose new position: " << endl;
                                int newPos;
                                cin >> newPos;
                                vector<Hero> Mover = Move.unitSwapMove(unitPos, newPos, Heroes);
                                Heroes.swap(Mover);
                            }
                            else if(selectedAction == 3)
                            {
                                cout << unitIndex[i] << " rests for this turn." << endl;
                            }
                        }
                    }
                    else if(classType == "BoneSoldier")
                    {
                        double modAcc = BoneSquad[unitPos - 1].getAccMod();

                        if(unitPos == 1 or unitPos == 2 or unitPos == 3)
                        {
                            int rngJesusTarget = (rand() % 3) + 1;

                            cout << BoneSquad[unitPos - 1].getName() << " tries to use Graveyard Slash against " << Heroes[rngJesusTarget - 1].getName() << endl;

                            double baseAcc = GrSlash.getBaseAcc();
                            double dodgeTarget = Heroes[rngJesusTarget - 1].getDodge();
                            double hitChance = baseAcc + modAcc - dodgeTarget;

                            int rngJesusHit = (rand() % 101);

                            if(rngJesusHit <= hitChance)
                            {
                                double rawDmg = GrSlash.UseMonsterAttack(BoneSquad, unitPos);
                                AttackAction(Heroes[rngJesusTarget - 1], rawDmg, Heroes);
                            } else{
                                cout << BoneSquad[unitPos - 1].getName() << " missed!" << endl;
                            }
                        }
                        else if(unitPos == 4)
                        {
                            int rngJesusTarget = (rand() % 2) + 1;

                            cout << BoneSquad[unitPos - 1].getName() << " tries to use Graveyard Stumble against " << Heroes[rngJesusTarget - 1].getName() << endl;

                            double baseAcc = GrStumble.getBaseAcc();
                            double dodgeTarget = Heroes[rngJesusTarget - 1].getDodge();
                            double hitChance = baseAcc + modAcc - dodgeTarget;

                            int rngJesusHit = (rand() % 101);

                            if(rngJesusHit <= hitChance)
                            {
                                double rawDmg = GrStumble.UseMonsterAttack(BoneSquad, unitPos);
                                AttackAction(Heroes[rngJesusTarget - 1], rawDmg, Heroes);

                                vector<Monster> Mover = Move.unitForwardMove(unitPos, BoneSquad);
                                BoneSquad.swap(Mover);
                            } else{
                                cout << BoneSquad[unitPos - 1].getName() << " missed!" << endl;
                            }
                        }
                    }
                    else if(classType == "BoneDefender")
                    {
                        double modAcc = BoneSquad[unitPos - 1].getAccMod();

                        int moveSelect = (rand() % 10) + 1;

                        if(unitPos == 1 or unitPos == 2)
                        {
                            if(moveSelect <= 5)
                            {
                                int rngJesusTarget = (rand() % 2) + 1;

                                cout << BoneSquad[unitPos - 1].getName() << " tries to use Axeblade against " << Heroes[rngJesusTarget - 1].getName() << endl;

                                double baseAcc = Axeblade.getBaseAcc();
                                double dodgeTarget = Heroes[rngJesusTarget - 1].getDodge();
                                double hitChance = baseAcc + modAcc - dodgeTarget;

                                int rngJesusHit = (rand() % 101);

                                if(rngJesusHit <= hitChance)
                                {
                                    double rawDmg = Axeblade.UseMonsterAttack(BoneSquad, unitPos);
                                    AttackAction(Heroes[rngJesusTarget - 1], rawDmg, Heroes);
                                } else
                                {
                                    cout << BoneSquad[unitPos - 1].getName() << " missed!" << endl;
                                }
                            } else
                            {
                                int rngJesusTarget = (rand() % 2) + 1;

                                cout << BoneSquad[unitPos - 1].getName() << " tries to use Dead Weight against " << Heroes[rngJesusTarget - 1].getName() << endl;

                                double baseAcc = DeadWeight.getBaseAcc();
                                double dodgeTarget = Heroes[rngJesusTarget - 1].getDodge();
                                double hitChance = baseAcc + modAcc - dodgeTarget;

                                int rngJesusHit = (rand() % 101);

                                if(rngJesusHit <= hitChance)
                                {
                                    double rawDmg = DeadWeight.UseMonsterAttack(BoneSquad, unitPos);
                                    int stunChance = DeadWeight.getStunBase() - Heroes[rngJesusTarget - 1].getStunRes();

                                    if(rawDmg / 1.5 == BoneSquad[unitPos - 1].getMaxDmg())
                                    {
                                        stunChance += 20;
                                    }

                                    AttackAction(Heroes[rngJesusTarget - 1], rawDmg, Heroes);

                                    int rngJesusStun = (rand() % 101);
                                    if(rngJesusStun <= stunChance)
                                    {
                                        Heroes[rngJesusTarget - 1].setStun();
                                        cout << Heroes[rngJesusTarget - 1].getName() << " Stunned!" << endl;
                                    } else
                                    {
                                        cout << BoneSquad[unitPos - 1].getName() << " couldn't inflict stun!" << endl;
                                    }
                                } else
                                {
                                    cout << BoneSquad[unitPos - 1].getName() << " missed!" << endl;
                                }
                            }
                        }
                        else if(unitPos == 3)
                        {
                            if(moveSelect <= 9)
                            {
                                int rngJesusTarget = (rand() % 2) + 1;

                                cout << BoneSquad[unitPos - 1].getName() << " tries to use Dead Weight against " << Heroes[rngJesusTarget - 1].getName() << endl;

                                double baseAcc = DeadWeight.getBaseAcc();
                                double dodgeTarget = Heroes[rngJesusTarget - 1].getDodge();
                                double hitChance = baseAcc + modAcc - dodgeTarget;

                                int rngJesusHit = (rand() % 101);

                                if(rngJesusHit <= hitChance)
                                {
                                    double rawDmg = DeadWeight.UseMonsterAttack(BoneSquad, unitPos);
                                    int stunChance = DeadWeight.getStunBase() - Heroes[rngJesusTarget - 1].getStunRes();

                                    if(rawDmg / 1.5 == BoneSquad[unitPos - 1].getMaxDmg())
                                    {
                                        stunChance += 20;
                                    }

                                    int rngJesusStun = (rand() % 101);
                                    if(rngJesusStun <= stunChance)
                                    {
                                        Heroes[rngJesusTarget - 1].setStun();
                                        cout << Heroes[rngJesusTarget - 1].getName()<< " Stunned!" << endl;
                                    } else
                                    {
                                        cout << BoneSquad[unitPos - 1].getName() << " couldn't inflict stun!" << endl;
                                    }
                                } else
                                {
                                    cout << BoneSquad[unitPos - 1].getName() << " missed!" << endl;
                                }
                            } else
                            {
                                int rngJesusTeammate = (rand() % 4) + 1;

                                cout << BoneSquad[unitPos - 1].getName() << " heals " << BoneSquad[rngJesusTeammate - 1].getName() << endl;

                                KnitBones.healTarget(BoneSquad, rngJesusTeammate);
                            }
                        }
                        else if(unitPos == 4)
                        {
                            int rngJesusTeammate = (rand() % 4) + 1;

                            cout << BoneSquad[unitPos - 1].getName() << " heals " << BoneSquad[rngJesusTeammate - 1].getName() << endl;

                            KnitBones.healTarget(BoneSquad, rngJesusTeammate);
                        }
                    }
                }
            }
            int deathCountHeroes = 0;
            int deathCountMonsters = 0;
            for(int i = 0; i < 4; i++)
            {
                if(Heroes[i].getSpeed() < 0)
                {
                    deathCountHeroes++;
                }
                if(deathCountHeroes == 4)
                {
                    isGameOverMonstersWin = true;
                    break;
                }
            }
            for(int i = 0; i < 4; i++)
            {
                if(BoneSquad[i].getSpeed() < 0)
                {
                    deathCountMonsters++;
                }
                if(deathCountMonsters == 4)
                {
                    isGameOverHeroesWin = true;
                    break;
                }
            }

            if(isGameOverHeroesWin or isGameOverMonstersWin)
            {
                break;
            }
        }

        if(isGameOverHeroesWin)
        {
            cout << "Our Heroes Finished This Skirmish Victorious!" << endl;
            break;
        }
        if(isGameOverMonstersWin)
        {
            cout << "Our Heroes Fell Down Against The Darkness..." << endl;
        }


        cout << "End of Round " << roundCount << endl;
        cout << " " << endl;
        roundCount++;
    }
    cout << endl;
    cout << "GAME OVER" << endl;
    cout << "Thanks for Playing." << endl;
}