#include "framework.h"
#include "Dun_Bullet.h"

Dun_Bullet::Dun_Bullet()
{
	_quad = make_shared<Quad>(L"Resource/Bullet.png");
	_quad->GetTransform()->SetScale({0.05, 0.05f});
}

Dun_Bullet::~Dun_Bullet()
{
}

void Dun_Bullet::Update()
{
	if(!_isActive)
		return;

	_quad->GetTransform()->AddVector2(_dir * _speed);

	_quad->Update();
}

void Dun_Bullet::Render()
{
	if (!_isActive)
		return;

	_quad->Render();
}

void Dun_Bullet::Shoot(Vector2 dir, Vector2 startPos)
{
	_isActive = true;

	_quad->GetTransform()->SetPosition(startPos);

	_dir = dir.NormalVector2();
	float angle = _dir.Angle();
	_quad->GetTransform()->SetAngle(angle);
}
