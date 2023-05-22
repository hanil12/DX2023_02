#include "framework.h"
#include "DungreedScene.h"

#include "../Object/Dungreed/Dun_Player.h"

DungreedScene::DungreedScene()
{
	_player = make_shared<Dun_Player>();

}

DungreedScene::~DungreedScene()
{
}

void DungreedScene::Update()
{
	if(KEY_PRESS('A'))
	{
		Vector2 curPos = _player->GetPos();
		_player->Move(curPos + Vector2(-0.1f,0.0f));
	}

	if (KEY_PRESS('D'))
	{
		Vector2 curPos = _player->GetPos();
		_player->Move(curPos + Vector2(0.1f, 0.0f));
	}

	_player->Update();
}

void DungreedScene::Render()
{
	_player->Render();
}
