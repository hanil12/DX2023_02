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

    cout << _name << "이 " << other->GetName() << "을" << _atk <<"만큼 공격했습니다." << endl;
    cout << "Boss의 공격!!!" << endl;
    other->Damaged(_atk);
}

void BossMonster::Damaged(int amount, shared_ptr<Creature> attacker)
{
    // TODO : Table에서 공격자가 있었으면 누적데미지에 추가, 없었으면 새로 AggroInfo만들어서 Table에 추가
    Creature::Damaged(amount);

    // 지금 당장 때린 얘가 어그로 테이블에 존재하는 얘.
    string name = attacker->GetName();
    auto iter = std::find_if(_aggroTable.begin(), _aggroTable.end(),
        [name](const AggroInfo& info)-> bool
        {
            if (info.attacker->GetName() == name)
                return true;
            return false;
        });

    // 찾았다
    if (iter != _aggroTable.end())
    {
        iter->totalDamage += amount;
    }
    // 처음 들어온 공격자 였다.
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
    // 죽어있으면 aggroTable에서 빼기
    auto iter = std::remove_if(_aggroTable.begin(), _aggroTable.end(), [](const AggroInfo& info)-> bool
        {
            if (info.attacker->IsAlive() == false)
                return true;
            return false;
        });

    _aggroTable.erase(iter, _aggroTable.end());

    // 높은 얘부터 정렬하기
    std::sort(_aggroTable.begin(), _aggroTable.end(), greater<AggroInfo>());

    // 어그로가 제일 높은 얘부터 4명 때리기
    int count = 0;

    for (auto info : _aggroTable)
    {
        if (count >= _range)
            break;

        Attack(info.attacker);

        count++;
    }

}
