#include "framework.h"
#include "Cup_Boss.h"

using namespace tinyxml2;

Cup_Boss::Cup_Boss()
{
	_collider = make_shared<RectCollider>(Vector2(250,400));
	_transform = make_shared<Transform>();
	_transform->SetParent(_collider->GetTransform());

	_collider->SetPosition(CENTER);
	_collider->GetTransform()->AddVector2(Vector2(300, 0));

	CreateAction(L"Resource/CupHead/BossStart.png", "Resource/CupHead/BossStart.xml", "IDLE", Vector2(250, 400), Action::END);
	CreateAction(L"Resource/CupHead/Boss_Loop.png", "Resource/CupHead/Boss_Loop.xml", "LOOP", Vector2(250, 400), Action::LOOP);
	CreateAction(L"Resource/CupHead/Boss_End.png", "Resource/CupHead/Boss_End.xml", "END", Vector2(250, 400), Action::END);
	CreateAction(L"Resource/CupHead/Clown_Page_Last_Die.png", "Resource/CupHead/Clown_Page_Last_Die.xml", "DEAD", Vector2(250, 400), Action::END);

	// Action Event ¼³Á¤
	{
		_actions[State::INTRO]->SetAlmostEndEvent([this]()->void { _state = State::LOOP; });
	}

	_intBuffer = make_shared<IntBuffer>();
}

Cup_Boss::~Cup_Boss()
{
}

void Cup_Boss::Update()
{
	_collider->Update();

	_actions[_state]->Update();
	_intBuffer->Update();

	_sprites[_state]->SetCurClip(_actions[_state]->GetCurClip());
	_sprites[_state]->Update();
	_transform->Update();
}

void Cup_Boss::Render()
{
	_transform->SetBuffer(0);
	_intBuffer->SetPSBuffer(1);
	_sprites[_state]->Render();

	_collider->Render();
}

void Cup_Boss::PostRender()
{
	ImGui::SliderInt("BossState", (int*)&_state, 0,3);
}

void Cup_Boss::CreateAction(wstring srvPath, string xmlPath, string actionName, Vector2 size, Action::Type type, CallBack event)
{
	shared_ptr<SRV> srv = ADD_SRV(srvPath);

	shared_ptr<tinyxml2::XMLDocument> document = make_shared<tinyxml2::XMLDocument>();
	string path = xmlPath;
	document->LoadFile(path.c_str());

	XMLElement* textureAtlas = document->FirstChildElement();
	XMLElement* row = textureAtlas->FirstChildElement();

	vector<Action::Clip> clips;

	while (true)
	{
		if (row == nullptr)
			break;

		int x = row->FindAttribute("x")->IntValue();
		int y = row->FindAttribute("y")->IntValue();
		int w = row->FindAttribute("w")->IntValue();
		int h = row->FindAttribute("h")->IntValue();

		Action::Clip clip = Action::Clip(x, y, w, h, srv);
		clips.push_back(clip);

		row = row->NextSiblingElement();
	}

	shared_ptr<Action> action = make_shared<Action>(clips, actionName, type);
	action->Play();
	action->SetEndEvent(event);
	shared_ptr<Sprite> sprite = make_shared<Sprite>(srvPath, size);

	action->Update();
	sprite->Update();

	_actions.push_back(action);
	_sprites.push_back(sprite);
}

void Cup_Boss::TakeDamage(int amount)
{
	_hp -= amount;

	if (_hp <= 0)
	{
		_hp = 0;
		_isActive = false;
	}
}
