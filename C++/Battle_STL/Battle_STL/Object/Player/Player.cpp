#include "framework.h"

Player::Player(int hp, int atk, string name)
: Creature(hp,atk,name)
{
	_type = CreatureType::PLAYER;
}

Player::~Player()
{
}