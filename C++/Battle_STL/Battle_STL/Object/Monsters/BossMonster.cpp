#include "framework.h"
#include "BossMonster.h"

BossMonster::BossMonster(int hp, int atk, string name)
: Monster(hp, atk, name)
{
    _type = CreatureType::AGGRO_ABLE;
}

BossMonster::~BossMonster()
{
}

void BossMonster::Attack(shared_ptr<Creature> other)
{
    if (!IsAlive() || !other->IsAlive())
        return;

    cout << _name << "�� " << other->GetName() << "��" << _atk <<"��ŭ �����߽��ϴ�." << endl;
    cout << "Boss�� ����!!!" << endl;
    other->Damaged(_atk);
}

void BossMonster::Damaged(int amount, shared_ptr<Creature> attacker)
{
    // TODO : Table���� �����ڰ� �־����� ������������ �߰�, �������� ���� AggroInfo���� Table�� �߰�
    Creature::Damaged(amount);

    // ���� ���� ���� �갡 ��׷� ���̺� �����ϴ� ��.
    string name = attacker->GetName();
    auto iter = std::find_if(_aggroTable.begin(), _aggroTable.end(),
        [name](const AggroInfo& info)-> bool
        {
            if (info.attacker->GetName() == name)
                return true;
            return false;
        });

    // ã�Ҵ�
    if (iter != _aggroTable.end())
    {
        iter->totalDamage += amount;
    }
    // ó�� ���� ������ ����.
    else
    {
        AggroInfo info;
        info.attacker = attacker;
        info.totalDamage = amount;

        _aggroTable.push_back(info);
    }
}

void BossMonster::AttackPlayersByAggroTable()
{
    // �׾������� aggroTable���� ����
    auto iter = std::remove_if(_aggroTable.begin(), _aggroTable.end(), [](const AggroInfo& info)-> bool
        {
            if (info.attacker->IsAlive() == false)
                return true;
            return false;
        });

    _aggroTable.erase(iter, _aggroTable.end());

    // ���� ����� �����ϱ�
    std::sort(_aggroTable.begin(), _aggroTable.end(), greater<AggroInfo>());

    // ��׷ΰ� ���� ���� ����� 4�� ������
    int count = 0;

    for (auto info : _aggroTable)
    {
        if (count >= _range)
            break;

        Attack(info.attacker);

        count++;
    }

}
