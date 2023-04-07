#include "framework.h"
#include "Bullet.h"

Bullet::Bullet()
{
	_circle = make_shared<CircleCollider>(Vector2(0, 0), 5);
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	if (_isActive == false)
		return;

	_circle->MoveCenter(_direction * _speed);
	_direction.y += GRAVITY;

	if (_circle->GetCenter().y > WIN_HEIGHT)
		_isActive = false;

	_circle->Update();
}

void Bullet::Render(HDC hdc)
{
	if (_isActive == false)
		return;

	_circle->Render(hdc);
}

void Bullet::Shoot(const Vector2& dir, float speed)
{
	_isActive = true;

	_direction = dir;
	_speed = speed;
}
