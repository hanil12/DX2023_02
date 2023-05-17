#include "framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
	_quad1 = make_shared<Quad>(L"Resource/Zelda.png");
	_quad2 = make_shared<Quad>(L"Resource/Goomba.png");

	_quad1->GetTransform()->SetParent(_quad2->GetTransform());

	_quad2->GetTransform()->SetPosition(CENTER);
	_quad1->GetTransform()->SetPosition(Vector2(1000,0));

	_quad2->GetTransform()->SetScale({0.1f, 0.1f});
}

TutorialScene::~TutorialScene()
{
}

void TutorialScene::Update()
{
	_angle1 += 0.0001f;
	_angle2 += 0.0003f;

	_quad1->GetTransform()->SetAngle(_angle1);
	_quad2->GetTransform()->SetAngle(_angle2);

	Vector2 temp = LERP(_quad2->GetTransform()->GetPos(), mousePos, 0.001f);
	_quad2->GetTransform()->SetPosition(temp);

	_quad1->Update();
	_quad2->Update();
}

void TutorialScene::Render()
{
	_quad2->Render();
	_quad1->Render();
}
