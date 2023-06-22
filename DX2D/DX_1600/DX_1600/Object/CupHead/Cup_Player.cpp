#include "framework.h"
#include "Cup_Player.h"
#include "Cup_Bullet.h"

using namespace tinyxml2;

Cup_Player::Cup_Player()
{
	SOUND->Add("Cup_Attack", "Resource/Sound/attack.wav");

	_col = make_shared<CircleCollider>(50);

	CreateAction(L"Resource/CupHead/Idle.png", "Resource/CupHead/Idle.xml", "IDLE", Vector2(250,250), Action::LOOP);
	CreateAction(L"Resource/CupHead/Jump.png", "Resource/CupHead/Jump.xml", "JUMP", Vector2(100,100), Action::LOOP);
	CreateAction(L"Resource/CupHead/Run.png", "Resource/CupHead/Run.xml", "RUN", Vector2(100,130), Action::LOOP);
	CreateAction(L"Resource/CupHead/Attack.png", "Resource/CupHead/Attack.xml", "ATTACK", Vector2(100,130), Action::END, std::bind(&Cup_Player::Attack, this));

	_sprites[0]->SetPS(ADD_PS(L"Shader/CupHeadPS.hlsl"));
	_intBuffer = make_shared<IntBuffer>();
	_intBuffer->_data.aInt = 0;
	_intBuffer->_data.bInt = 300;

	_transform = make_shared<Transform>();
	_transform->SetParent(_col->GetTransform());
	_transform->SetPosition(Vector2(0.0f,9.876f));

	SetAction(IDLE);

	bullet = make_shared<Cup_Bullet>();
}

Cup_Player::~Cup_Player()
{
}

void Cup_Player::Update()
{
	Input();
	Jump();

	_col->Update();

	_actions[_curState]->Update();
	_intBuffer->Update();
	_sprites[_curState]->Update();
	_transform->Update();

	bullet->Update();
}

void Cup_Player::Render()
{
	_transform->SetBuffer(0);
	_sprites[_curState]->SetCurClip(_actions[_curState]->GetCurClip());
	_intBuffer->SetPSBuffer(1);
	_sprites[_curState]->Render();

	_col->Render();

	bullet->Render();
}

void Cup_Player::PostRender()
{
	ImGui::SliderInt("State", (int*)&_curState, 0, 3);

	ImGui::SliderInt("isMosaic", &_intBuffer->_data.aInt,0,1);
	ImGui::SliderInt("Mosaic Magnitude", &_intBuffer->_data.bInt,0,300);
}

void Cup_Player::CreateAction(wstring srvPath, string xmlPath, string actionName, Vector2 size, Action::Type type, CallBack event)
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

	shared_ptr<Action> action = make_shared<Action>(clips, actionName, type);
	action->Play();
	action->SetEndEvent(event);
	shared_ptr<Sprite> sprite = make_shared<Sprite>(srvPath, size);

	_actions.push_back(action);
	_sprites.push_back(sprite);
}

void Cup_Player::Input()
{
	if (KEY_DOWN(VK_LBUTTON) && _isAttack == false && _isFalling == false)
	{
		SOUND->Play("Cup_Attack", 0.3f);
		_isAttack = true;
		SetAction(ATTACK);
	}

	if (KEY_PRESS('A'))
	{
		Move(LEFT_VECTOR);
		SetLeft();
	}

	if (KEY_PRESS('D'))
	{
		Move(RIGHT_VECTOR);
		SetRight();
	}

	if (KEY_DOWN(VK_SPACE) && _isFalling == false)
	{
		_jumpPower = 1000.0f;
		_isFalling = true;
	}

	if(_curState != RUN && _curState != IDLE)
		return;

	if(KEY_PRESS('A') || KEY_PRESS('D'))
		SetAction(RUN);
	else if(_curState == RUN)
		SetAction(IDLE);
}

void Cup_Player::Jump()
{
	if(_isFalling == true)
		SetAction(JUMP);
	else if(_curState == JUMP && _isFalling == false)
		SetAction(IDLE);

	// 중력적용
	{
		_jumpPower -= 15;

		if(_jumpPower < -600.0f)
			_jumpPower = -600.0f;

		_col->GetTransform()->AddVector2(Vector2(0, 1) * _jumpPower * DELTA_TIME);
	}
}

void Cup_Player::Attack()
{
	_isAttack = false;
	SetAction(IDLE);

	bullet->Fire(_col->GetTransform()->GetWorldPosition(), RIGHT_VECTOR);
}

void Cup_Player::SetAction(State state)
{
	_curState = state;

	if(_curState == _oldState)
		return;

	_actions[_curState]->Play();
	_actions[_oldState]->Reset();
	_oldState = _curState;
}

void Cup_Player::SetLeft()
{
	for(auto sprite : _sprites)
		sprite->SetLeft();
}

void Cup_Player::SetRight()
{
	for (auto sprite : _sprites)
		sprite->SetRight();
}
