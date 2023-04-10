#include "framework.h"
#include "Bullet.h"

Bullet::Bullet()
{
	_collider = make_shared<CircleCollider>(Vector2(0, 0), 5);
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	if (_isActive == false)
		return;

	_collider->MoveCenter(_direction * _speed);
	_direction.y += GRAVITY;

	if (_collider->GetCenter().y > WIN_HEIGHT)
		_isActive = false;

	_collider->Update();
}

void Bullet::Render(HDC hdc)
{
	if (_isActive == false)
		return;

	_collider->Render(hdc);
}

void Bullet::Shoot(const Vector2& dir, float speed)
{
	_isActive = true;

	_direction = dir;
	_speed = speed;
}

bool Bullet::IsCollision(shared_ptr<class Cannon> cannon)
{
	if (_collider->IsCollision(cannon->GetCollider()))
	{
		return true;
	}

	return false;
}
