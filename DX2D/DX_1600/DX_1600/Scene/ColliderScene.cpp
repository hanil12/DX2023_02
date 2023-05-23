#include "framework.h"
#include "ColliderScene.h"

ColliderScene::ColliderScene()
{
	_rectCollider = make_shared<RectCollider>(Vector2(100.0f, 100.0f));

	_rectCollider->SetPosition(CENTER);
}

ColliderScene::~ColliderScene()
{
}

void ColliderScene::Update()
{
	_rectCollider->Update();
}

void ColliderScene::Render()
{
	_rectCollider->Render();
}

void ColliderScene::PostRender()
{
}
