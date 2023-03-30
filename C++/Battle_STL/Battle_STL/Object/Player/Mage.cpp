#include "framework.h"
#include "Mage.h"

Mage::Mage(int hp, int atk, string name)
: Player(hp, atk, name)
{
    _type = CreatureType::PLAYER;
}

Mage::~Mage()
{
}

void Mage::Attack(shared_ptr<Creature> creature)
{
    if (!IsAlive() || !creature->IsAlive())
        return;

    creature->Damaged(_atk);
    cout << _name << "이 " << creature->GetName() << "을 공격했습니다." << endl;
    cout << "Mage의 공격!!!" << endl;
}
