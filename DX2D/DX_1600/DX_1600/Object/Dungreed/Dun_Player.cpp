#include "framework.h"
#include "Dun_Player.h"

#include "Dun_Bullet.h"

Dun_Player::Dun_Player()
{
	_quad = make_shared<Quad>(L"Resource/Player.png");
	_transform = make_shared<Transform>();

	_bowSlot = make_shared<Transform>();

	_bow = make_shared<Quad>(L"Resource/Bow.png");
	_bowTrans = make_shared<Transform>();
	_bowTrans->SetParent(_bowSlot);
	_bowTrans->SetPosition({50,0});
	_bowTrans->SetAngle(-PI * 0.75f);

	for (int i = 0; i < 30; i++)
	{
		shared_ptr<Dun_Bullet> bullet = make_shared<Dun_Bullet>();
		bullet->_isActive = false;
		_bullets.push_back(bullet);
	}
}

Dun_Player::~Dun_Player()
{
}

void Dun_Player::Update()
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x0001)
	{
		Fire();
	}

	SetBowAngle();

	_bowSlot->SetPosition(_transform->GetPos());

	_transform->Update();
	_bowSlot->Update();
	_bowTrans->Update();

	for(auto bullet : _bullets)
		bullet->Update();
}

void Dun_Player::Render()
{
	_transform->SetBuffer(0);
	_quad->Render();
	_bowTrans->SetBuffer(0);
	_bow->Render();

	for(auto bullet : _bullets)
		bullet->Render();
}

void Dun_Player::SetBowAngle()
{
	Vector2 playerToMouse = MOUSE_POS - GetPos();
	float angle = playerToMouse.Angle();
	_bowSlot->SetAngle(angle);
}

bool Dun_Player::IsCollision_Bullets(shared_ptr<Collider> col)
{
	for (auto bullet : _bullets)
	{
		if(bullet->_isActive == false)
			continue;

		if (col->IsCollision(bullet->GetCollider()))
		{
			bullet->_isActive = false;
			return true;
		}
	}

	return false;
}

void Dun_Player::Fire()
{
	Vector2 dir = MOUSE_POS - GetPos();

	auto bulletIter = std::find_if(_bullets.begin(), _bullets.end(), 
	[](const shared_ptr<Dun_Bullet> obj)-> bool { return !obj->_isActive; });

	if(bulletIter == _bullets.end())
		return;

	(*bulletIter)->Shoot(dir, _bowTrans->GetWorldPosition());
}
