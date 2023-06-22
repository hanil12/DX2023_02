#include "framework.h"
#include "DungreedScene.h"

#include "../../Object/Dungreed/Dun_Player_Advanced.h"
#include "../../Object/Dungreed/Dun_Boss.h"

DungreedScene::DungreedScene()
{
	_player = make_shared<Dun_Player_Advanced>();
	_player->SetPosition(CENTER);

	_floor = make_shared<RectCollider>(Vector2((float)WIN_WIDTH, 100.0f));
	_floor->SetPosition(Vector2(CENTER.x, 50.0f));

	_boss = make_shared<Dun_Boss>();
	_boss->SetPostion(Vector2(WIN_WIDTH - 100.0f, WIN_HEIGHT - 100.0f));
}

DungreedScene::~DungreedScene()
{
}

void DungreedScene::Update()
{
	_player->Update();
	_boss->Update();

	_player->SetFalling(!_floor->Block(_player->GetCollider()));

	if (_boss->_isActive)
	{
		if (_player->IsCollision_Bullets(_boss->GetCollider()))
			_boss->Damaged(5);
	}

	_player->Collider_Update();
	_floor->Update();
	_boss->Collider_Update();
}

void DungreedScene::Render()
{
	_player->Render();
	_boss->Render();
	_floor->Render();
}

void DungreedScene::PostRender()
{
	ImGui::Text("mouseX : %d, mouseY : %d", (int)MOUSE_POS.x, (int)MOUSE_POS.y);
}
