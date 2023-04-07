#include "framework.h"
#include "CannonScene.h"

CannonScene::CannonScene()
{
	_cannon = make_shared<Cannon>(Vector2(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f));
}

CannonScene::~CannonScene()
{
}

void CannonScene::Update()
{
	_cannon->Update();
}

void CannonScene::Render(HDC hdc)
{
	_cannon->Render(hdc);
}
