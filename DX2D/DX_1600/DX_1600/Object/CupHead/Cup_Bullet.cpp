#include "framework.h"
#include "Cup_Bullet.h"

using namespace tinyxml2;

Cup_Bullet::Cup_Bullet()
{
	_col = make_shared<CircleCollider>(5.0f);

	CreateAction(L"Resource/CupHead/Bullet_Intro.png", "Resource/CupHead/Bullet_Intro.xml", "Intro", Vector2(50, 150), Action::END);
	CreateAction(L"Resource/CupHead/Bullet_Loop.png", "Resource/CupHead/Bullet_Loop.xml", "Loop", Vector2(50, 150), Action::LOOP);

	_transform = make_shared<Transform>();
	_transform->SetParent(_col->GetTransform());
	_transform->SetAngle(- PI * 0.5f);
	_transform->SetPosition(Vector2(-50.0f, 0.0f));

	_actions[INTRO]->SetEndEvent(std::bind(&Cup_Bullet::EndEvent, this));
}

Cup_Bullet::~Cup_Bullet()
{
}

void Cup_Bullet::Update()
{
	if(_isActive == false)
		return;

	_col->GetTransform()->AddVector2(_direction * _speed * DELTA_TIME);

	_col->Update();

	_actions[_curState]->Update();
	_sprites[_curState]->Update();
	_transform->Update();
}

void Cup_Bullet::Render()
{
	if(_isActive == false)
		return;

	_transform->SetBuffer(0);
	_sprites[_curState]->SetCurFrame(_actions[_curState]->GetCurClip());
	_sprites[_curState]->Render();

	_col->Render();
}

void Cup_Bullet::CreateAction(wstring srvPath, string xmlPath, string actionName, Vector2 size, Action::Type type, CallBack event)
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

	_actions.push_back(action);
	_sprites.push_back(sprite);
}

void Cup_Bullet::Fire(Vector2 startPos, Vector2 dir)
{
	_isActive = true;
	_curState = INTRO;
	_actions[_curState]->Play();
	_actions[LOOP]->Reset();

	_col->GetTransform()->SetPosition(startPos);
	if (dir.x > 0.0f)
	{
		_direction = RIGHT_VECTOR;
		SetRight();
	}
	else
	{
		_direction = LEFT_VECTOR;
		SetLeft();
	}
}

void Cup_Bullet::EndEvent()
{
	_curState = LOOP;
	_actions[LOOP]->Play();
}

void Cup_Bullet::SetLeft()
{
	for (auto sprite : _sprites)
		sprite->SetLeft();
}

void Cup_Bullet::SetRight()
{
	for (auto sprite : _sprites)
		sprite->SetRight();
}
