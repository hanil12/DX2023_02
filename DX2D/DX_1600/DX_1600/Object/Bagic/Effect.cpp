#include "framework.h"
#include "Effect.h"

Effect::Effect(string name, wstring file, Vector2 maxFrame, Vector2 size, float speed, Action::Type type)
{
	_transform = make_shared<Transform>();
	CreateAction(name,file, maxFrame, size, speed, type);
}

Effect::~Effect()
{
}

void Effect::Update()
{
	if(!_isActive)	return;

	_transform->Update();
	_action->Update();
	_sprite->SetCurClip(_action->GetCurClip());
	_sprite->Update();
}

void Effect::Render()
{
	if (!_isActive)	return;

	_transform->SetBuffer(0);
	_sprite->Render();
}

void Effect::Play(Vector2 pos)
{
	_isActive = true;
	_action->Play();
	_transform->SetPosition(pos);
}

void Effect::End()
{
	_isActive = false;
	_action->Reset();
}

void Effect::CreateAction(string name, wstring file, Vector2 maxFrame, Vector2 size, float speed, Action::Type type)
{
	_sprite = make_shared<Sprite>(file, maxFrame, size);
	shared_ptr<SRV> srv = ADD_SRV(file);

	vector<Action::Clip> clips;

	Vector2 clipSize = _sprite->GetImageSize();
	clipSize.x /= maxFrame.x;
	clipSize.y /= maxFrame.y;

	for (int y = 0; y < maxFrame.y; y++)
	{
		for (int x = 0; x < maxFrame.x; x++)
		{
			Action::Clip clip = Action::Clip(x* clipSize.x, y * clipSize.y, clipSize.x, clipSize.y, srv);
			clips.push_back(clip);
		}
	}

	_action = make_shared<Action>(clips, name, type, speed);
	_action->SetEndEvent(std::bind(&Effect::End, this));
}
