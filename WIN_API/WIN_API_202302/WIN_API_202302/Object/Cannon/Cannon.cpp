#include "framework.h"
#include "Cannon.h"

Cannon::Cannon(Vector2 pos)
{
	_body = make_shared<CircleCollider>(pos, 50);
	_muzzle = make_shared<Line>(Vector2(pos), Vector2(pos.x + _muzzleLength, pos.y));

	// ¿ÀºêÁ§Æ® Ç®¸µ
	for (int i = 0; i < 30; i++)
	{
		shared_ptr<Bullet> bullet = make_shared<Bullet>();
		_bullets.push_back(bullet);
	}
}

Cannon::~Cannon()
{
}

void Cannon::Update()
{
	Move();
	Angle();
	Fire();

	_body->Update();
	_muzzle->Update();

	for (auto& bullet : _bullets)
	{
		bullet->Update();
	}
}

void Cannon::Render(HDC hdc)
{
	_muzzle->Render(hdc);
	_body->Render(hdc);

	for (auto& bullet : _bullets)
	{
		bullet->Render(hdc);
	}
}

void Cannon::Move()
{
	if (GetAsyncKeyState(VK_LEFT))
	{
		_body->MoveCenter(Vector2(-1.0f, 0.0f));
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		_body->MoveCenter(Vector2(1.0f, 0.0f));
	}

	_muzzle->_start = _body->GetCenter();
	_muzzle->_end = _muzzle->_start + _muzzleDir * _muzzleLength;
}

void Cannon::Angle()
{
	if (GetAsyncKeyState(VK_UP))
	{
		_muzzleAngle += 0.1f;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		_muzzleAngle -= 0.1f;
	}

	_muzzleDir = Vector2(cosf(_muzzleAngle), -sinf(_muzzleAngle));
}

void Cannon::Fire()
{
	if (GetAsyncKeyState(VK_SPACE))
	{
		// ²¨Á®ÀÖ´Â ¾Ö¸¸ ½¸
		auto iter = std::find_if(_bullets.begin(), _bullets.end(),
			[](const shared_ptr<Bullet>& bullet)-> bool
			{
				if (bullet->IsActive() == false)
					return true;
				return false;
			});

		if (iter != _bullets.end())
		{
			// ²¨Á®ÀÖ´Â ¾ê°¡ ÀÖ´Â °æ¿ì ½¸!!
			(*iter)->SetPos(_muzzle->_end);
			(*iter)->Shoot(_muzzleDir.NormalVector2(), 10.0f);
		}
	}
}
