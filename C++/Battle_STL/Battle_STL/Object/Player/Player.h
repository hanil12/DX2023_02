#pragma once
class Creature;
class Player : public Creature
{
public:
	Player(int hp, int atk, string name);
	virtual ~Player();

protected:

};

