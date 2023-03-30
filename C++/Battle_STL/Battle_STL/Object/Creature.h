#pragma once
class Creature
{
public:
	Creature(int hp, int atk, string name);
	virtual ~Creature();

	virtual void Attack(shared_ptr<Creature> creature) abstract;
	virtual void PrintInfo();

	virtual void Damaged(int amount, shared_ptr<Creature> attack = nullptr);
	bool IsAlive() const;

	const string& GetName() { return _name; }
	const CreatureType& GetType() { return _type; }

protected:
	int _hp;
	int _atk;
	string _name;
	CreatureType _type;
};

