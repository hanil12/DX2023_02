#include "framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
	_quad1 = make_shared<Quad>(L"Resource/Zelda.png");
	_quad2 = make_shared<Quad>(L"Resource/Goomba.png");
}

TutorialScene::~TutorialScene()
{
}

void TutorialScene::Update()
{
	_quad1->Update();
	_quad2->Update();
}

void TutorialScene::Render()
{
	_quad2->Render();
	_quad1->Render();
}
