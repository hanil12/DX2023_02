#include "framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
	_quad1 = make_shared<Quad>(L"Resource/Zelda.png");
	_quad2 = make_shared<Quad>(L"Resource/Goomba.png");

	_world = make_shared<MatrixBuffer>();
	_view = make_shared<MatrixBuffer>();
	_projection = make_shared<MatrixBuffer>();

	XMMATRIX projectM = XMMatrixOrthographicOffCenterLH(0,WIN_WIDTH,0,WIN_HEIGHT, 0.0f, 1.0f);

	_projection->SetData(projectM);

	_world->Update();
	_view->Update();
	_projection->Update();
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
	_world->SetVSBuffer(0);
	_view->SetVSBuffer(1);
	_projection->SetVSBuffer(2);

	_quad2->Render();
	_quad1->Render();
}
