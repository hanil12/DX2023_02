#include <iostream>

using namespace std;

#include "Creature.h"
#include "framework.h"

Monster::Monster(int hp, int atk, string name)
: Creature(hp,atk,name)
{
    _type = CreatureType::MONSTER;
}

Monster::~Monster()
{
}

void Monster::Attack(shared_ptr<Creature> creature)
{
    if (!IsAlive() || !creature->IsAlive())
        return;

    creature->Damaged(_atk);
    cout << _name << "이 " << creature->GetName() << "을 공격했습니다." << endl;
    cout << "Monster 공격!!!" << endl;
}
