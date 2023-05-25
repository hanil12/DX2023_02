#include "framework.h"
#include "ColliderScene.h"

ColliderScene::ColliderScene()
{
	_rectCollider = make_shared<RectCollider>(Vector2(100.0f, 100.0f));
	_circleCollider = make_shared<CircleCollider>(50);
	_circleCollider2 = make_shared<CircleCollider>(100);
	_circleCollider2->SetParent(_rectCollider->GetTransform());

	_rectCollider->SetPosition(CENTER);
	_rectCollider->SetScale(Vector2(2.0f,2.0f));
	_circleCollider2->SetPosition(Vector2(100.0f, 0.0f));
}

ColliderScene::~ColliderScene()
{
}

void ColliderScene::Update()
{
	_rectCollider->Update();
	_circleCollider->Update();
	_circleCollider2->Update();

	if (_circleCollider->IsCollision(_rectCollider))
		_circleCollider->SetRed();
	else
		_circleCollider->SetGreen();

	_circleCollider->SetPosition(MOUSE_POS);
	_circleCollider->Block(_circleCollider2);
}

void ColliderScene::Render()
{
	_rectCollider->Render();
	_circleCollider->Render();
	_circleCollider2->Render();
}

void ColliderScene::PostRender()
{
	//ImGui::SliderFloat2("CirclePos", (float*)&_circlePos, 0, 1280);
	//_circleCollider->SetPosition(_circlePos);
}
