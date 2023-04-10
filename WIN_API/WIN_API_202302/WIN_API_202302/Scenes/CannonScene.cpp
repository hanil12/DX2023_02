#include "framework.h"
#include "CannonScene.h"

CannonScene::CannonScene()
{
	_cannon = make_shared<Cannon>(Vector2(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f));
	_cannonEnemy = make_shared<Cannon>(Vector2(WIN_WIDTH * 0.5f + 300.0f, WIN_HEIGHT * 0.5f));

	_cannon->SetTurn(true);
	_cannonEnemy->SetTurn(false);

	// _cannon->SetTarget(_cannonEnemy);
}

CannonScene::~CannonScene()
{
}

void CannonScene::Update()
{
	_cannon->Update();
	_cannonEnemy->Update();

	// ĳ���� ����ִ� �Ѿ� 30���� ���ʹ��� �浹�˻�
	for (auto bullet : _cannon->GetBullets())
	{
		if (bullet->IsCollision(_cannonEnemy))
		{
			bullet->SetActive(false);
		}
	}
}

void CannonScene::Render(HDC hdc)
{
	_cannon->Render(hdc);
	_cannonEnemy->Render(hdc);
}
