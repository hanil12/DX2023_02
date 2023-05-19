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
	_player->Update();
}

void DungreedScene::Render()
{
	_player->Render();
}
