#include "framework.h"
#include "Dun_Bullet.h"

Dun_Bullet::Dun_Bullet()
{
	_collider = make_shared<CircleCollider>(5.0f);
	_quad = make_shared<Quad>(L"Resource/Bullet.png");

	_quad->GetTransform()->SetParent(_collider->GetTransform());
	_quad->GetTransform()->SetScale({0.05, 0.05f});
	_quad->GetTransform()->SetPosition({-10.0f, 0.0f});
}

Dun_Bullet::~Dun_Bullet()
{
}

void Dun_Bullet::Collider_Update()
{
	if(!_isActive)
		return;
	_collider->Update();
}

void Dun_Bullet::Update()
{
	if(!_isActive)
		return;

	_collider->GetTransform()->AddVector2(_dir * _speed * DELTA_TIME);

	_quad->Update();
}

void Dun_Bullet::Render()
{
	if (!_isActive)
		return;

	_quad->Render();
	_collider->Render();
}

void Dun_Bullet::Shoot(Vector2 dir, Vector2 startPos)
{
	_isActive = true;

	_collider->GetTransform()->SetPosition(startPos);

	_dir = dir.NormalVector2();
	float angle = _dir.Angle();
	_collider->GetTransform()->SetAngle(angle);
}
