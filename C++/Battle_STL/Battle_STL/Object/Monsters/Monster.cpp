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
    cout << _name << "�� " << creature->GetName() << "�� �����߽��ϴ�." << endl;
    cout << "Monster ����!!!" << endl;
}
