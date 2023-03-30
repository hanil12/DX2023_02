#include "framework.h"

Creature::Creature(int hp, int atk, string name)
: _hp(hp)
, _atk(atk)
, _name(name)
{
    _type = CreatureType::NONE;
}

Creature::~Creature()
{
}

void Creature::PrintInfo()
{
    cout << "Name : " << _name << endl;
    cout << "HP : " << _hp << endl;
    cout << "ATK : " << _atk << endl;
}

void Creature::Damaged(int amount, shared_ptr<Creature> attack)
{
    _hp -= amount;

    if (_hp < 0)
    {
        _hp = 0;
    }

    cout << _name << "ÀÇ Ã¼·Â: " << _hp << endl;
}

bool Creature::IsAlive() const
{
    return _hp > 0;
}
