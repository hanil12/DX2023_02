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
        // TODO : �ڱ� �ڽ��� ����Ű�� shared_ptr�� �Ѱܾ��Ѵ�.
        other->Damaged(_atk, shared_from_this());
    }
    else
    {
        other->Damaged(_atk);
    }
    cout << _name << "�� " << other->GetName() << "�� " << _atk << "��ŭ �����߽��ϴ�." << endl;
    cout << "Knight�� ����!!!" << endl;
}
