#pragma once
class Creature;
class Monster : public Creature
{
public:
	Monster(int hp, int atk, string name);
	virtual ~Monster();

	virtual void Attack(shared_ptr<Creature> creature) override;

protected:

};

