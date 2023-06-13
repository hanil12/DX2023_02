#include "framework.h"
#include "Dun_Boss.h"

Dun_Boss::Dun_Boss()
{
	_quad = make_shared<Quad>(L"Resource/Goomba.png");
	_transform = make_shared<Transform>();

	_collider = make_shared<CircleCollider>(_quad->GetQuadHalfSize().x);

	_transform->SetParent(_collider->GetTransform());
	_collider->GetTransform()->SetScale(Vector2(0.5f,0.5f));
}

Dun_Boss::~Dun_Boss()
{
}

void Dun_Boss::Collider_Update()
{
	if(!_isActive) return;

	_collider->Update();
}

void Dun_Boss::Update()
{
	if (!_isActive) return;

	_transform->Update();
}

void Dun_Boss::Render()
{
	if (!_isActive) return;

	_transform->SetBuffer(0);
	_quad->Render();
	_collider->Render();
}

void Dun_Boss::Damaged(int amount)
{
	if (!_isActive) return;

	_hp -= amount;

	if(_hp <= 0)
		_isActive = false;
}
