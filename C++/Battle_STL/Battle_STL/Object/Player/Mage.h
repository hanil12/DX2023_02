#pragma once
class Mage : public Player
{
public:
	Mage(int hp, int atk, string name);
	virtual ~Mage();

	virtual void Attack(shared_ptr<Creature> creature) override;
private:
};

