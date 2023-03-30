#include "framework.h"
#include "Knight.h"

Knight::Knight(int hp, int atk, string name)
: Player(hp, atk, name)
{
    _type = CreatureType::PLAYER;
}

Knight::~Knight()
{
}

void Knight::Attack(shared_ptr<Creature> other)
{
    if (!IsAlive() || !other->IsAlive())
        return;

    if (other->GetType() == CreatureType::AGGRO_ABLE)
    {
        // TODO : 자기 자신을 가리키는 shared_ptr을 넘겨야한다.
        other->Damaged(_atk, shared_from_this());
    }
    else
    {
        other->Damaged(_atk);
    }
    cout << _name << "이 " << other->GetName() << "을 " << _atk << "만큼 공격했습니다." << endl;
    cout << "Knight의 공격!!!" << endl;
}
