#include "framework.h"
#include "Cup_Player.h"

using namespace tinyxml2;

Cup_Player::Cup_Player()
{
	_col = make_shared<CircleCollider>(50);

	CreateAction();

	_transform = make_shared<Transform>();
	_transform->SetParent(_col->GetTransform());
	_transform->SetPosition(Vector2(0,9.876));
}

Cup_Player::~Cup_Player()
{
}

void Cup_Player::Update()
{
	Input();

	_col->Update();

	_action->Update();
	_sprite->Update();
	_transform->Update();

	// 중력적용
	{
		_jumpPower -= DELTA_TIME * 500.0f;

		_col->GetTransform()->AddVector2(Vector2(0,1) * _jumpPower * DELTA_TIME);
	}
}

void Cup_Player::Render()
{
	_transform->SetBuffer(0);
	_sprite->SetCurFrame(_action->GetCurClip());
	_sprite->Render();

	_col->Render();
}

void Cup_Player::PostRender()
{
	//ImGui::SliderFloat2("FixedPos", (float*)&_fixedPos,0,100);
	//_transform->SetPosition(_fixedPos);
}

void Cup_Player::CreateAction()
{
	wstring srvPath = L"Resource/CupHead/Idle.png";
	shared_ptr<SRV> srv = ADD_SRV(srvPath);

	shared_ptr<tinyxml2::XMLDocument> document = make_shared<tinyxml2::XMLDocument>();
	string path = "Resource/CupHead/Idle.xml";
	document->LoadFile(path.c_str());

	XMLElement* textureAtlas = document->FirstChildElement();
	XMLElement* row = textureAtlas->FirstChildElement();

	vector<Action::Clip> clips;

	while (true)
	{
		if(row == nullptr)
			break;

		int x = row->FindAttribute("x")->IntValue();
		int y = row->FindAttribute("y")->IntValue();
		int w = row->FindAttribute("w")->IntValue();
		int h = row->FindAttribute("h")->IntValue();

		Action::Clip clip = Action::Clip(x,y,w,h,srv);
		clips.push_back(clip);

		row = row->NextSiblingElement();
	}

	_action = make_shared<Action>(clips, "CUP_IDLE");
	_action->Play();
	_sprite = make_shared<Sprite>(srvPath, Vector2(250,250));
}

void Cup_Player::Input()
{
	if(KEY_PRESS('A'))
		_sprite->SetLeft();
	if(KEY_PRESS('D'))
		_sprite->SetRight();
}
