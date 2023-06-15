#include "framework.h"
#include "ActionScene.h"

ActionScene::ActionScene()
{
	CreateAction();
	Vector2 size = ADD_SRV(L"Resource/zelda_sprite.png")->GetImageSize();
	size.x /= 10;
	size.y /= 8;
	_sprite = make_shared<Sprite>(L"Resource/zelda_sprite.png", Vector2(10,8), size);
	_transform = make_shared<Transform>();

	_transform->SetPosition(CENTER);

	// Listner 패턴, Observer 패턴, 구독자 패턴
	_action->SetEndEvent(std::bind(&ActionScene::EndEvent,this));
}

ActionScene::~ActionScene()
{
}

void ActionScene::Update()
{
	_sprite->Update();
	_transform->Update();
	_action->Update();
}

void ActionScene::Render()
{
	_transform->SetBuffer(0);
	_sprite->SetCurClip(_action->GetCurClip());
	_sprite->Render();
}

void ActionScene::PostRender()
{
	if(_isEnd)
		ImGui::Text("EndEvent!!!");
}

void ActionScene::CreateAction()
{
	// 앞으로 걸어다니는 액션
	vector<Action::Clip> clips;
	{
		shared_ptr<SRV> srv = ADD_SRV(L"Resource/zelda_sprite.png");
		Vector2 imageSize = srv->GetImageSize();
		Vector2 maxFrame = {10,8};
		float w = imageSize.x / maxFrame.x;
		float h = imageSize.y / maxFrame.y;

		for (int i = 0; i < 10; i++)
		{
			Action::Clip clip1 = Action::Clip(w * i, h * 4, w,h, srv);
			clips.push_back(clip1);
		}
	}

	_action = make_shared<Action>(clips, "RUN_F", Action::Type::END);
	_action->Play();
}
