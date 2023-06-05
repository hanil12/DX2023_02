#include "framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
	_quad1 = make_shared<Quad>(L"Resource/Zelda.png");
	_transform1 = make_shared<Transform>();

	_quad2 = make_shared<Quad>(L"Resource/Goomba.png");
	_transform2 = make_shared<Transform>();

	_transform1->SetParent(_transform2);

	_transform2->SetPosition(CENTER);
	_transform1->SetPosition(Vector2(1000,0));

	_transform2->SetScale({0.1f, 0.1f});
}

TutorialScene::~TutorialScene()
{
}

void TutorialScene::Update()
{
	_angle1 += 0.0001f;
	_angle2 += 0.0003f;

	_transform1->SetAngle(_angle1);
	_transform2->SetAngle(_angle2);

	Vector2 temp = LERP(_transform2->GetPos(), MOUSE_POS, 0.001f);
	_transform2->SetPosition(temp);

	_transform1->Update();
	_transform2->Update();
}

void TutorialScene::Render()
{
	_quad2->Render();
	_quad1->Render();
}
