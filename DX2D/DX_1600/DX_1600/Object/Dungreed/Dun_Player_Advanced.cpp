#include "framework.h"
#include "Dun_Bullet.h"
#include "Dun_Player.h"
#include "Dun_Player_Advanced.h"

Dun_Player_Advanced::Dun_Player_Advanced()
{
	_collider = make_shared<CircleCollider>(50.0f);

	_transform->SetParent(_collider->GetTransform());
	_bowSlot->SetParent(_collider->GetTransform());
}

Dun_Player_Advanced::~Dun_Player_Advanced()
{
}

void Dun_Player_Advanced::Collider_Update()
{
	for(auto bullet : _bullets)
		bullet->Collider_Update();

	_collider->Update();
}

void Dun_Player_Advanced::Update()
{
	Input();
	Falling();

	Dun_Player::Update();
}

void Dun_Player_Advanced::Render()
{
	Dun_Player::Render();
	_collider->Render();
}

void Dun_Player_Advanced::Input()
{
	if (KEY_PRESS('A'))
	{
		Vector2 movePos = Vector2(-_speed, 0.0f) * DELTA_TIME;
		Move(movePos);
	}

	if (KEY_PRESS('D'))
	{
		Vector2 movePos = Vector2(_speed, 0.0f) * DELTA_TIME;
		Move(movePos);
	}
}

void Dun_Player_Advanced::Falling()
{
	if (_isFalling == false)
	{
		_fallingVec = {0.0f,0.0f};
		return;
	}

	_fallingVec.y -= (float)(GRAV) * DELTA_TIME;
	Move(_fallingVec);
}
