#include "framework.h"
#include "CupHeadScene.h"

#include "../../Object/CupHead/Cup_Player.h"

CupHeadScene::CupHeadScene()
{
	_player = make_shared<Cup_Player>();
	_player->SetPosition(CENTER);

	_track = make_shared<Quad>(L"Resource/CupHead/track.png");
	_transform = make_shared<Transform>();
	Vector2 trackSize = _track->GetImageSize();
	_col = make_shared<RectCollider>(trackSize * 2.0f);

	_transform->SetParent(_col->GetTransform());
	_transform->SetPosition(Vector2(0,75));

	Vector2 pos = CENTER;
	pos.y -= 350.0f;
	_col->GetTransform()->SetPosition(pos);
}

CupHeadScene::~CupHeadScene()
{
}

void CupHeadScene::Update()
{
	_player->Update();

	_transform->Update();
	_col->Update();

	if(_col->Block(_player->GetCollider()))
		_player->SetGrounded();
}

void CupHeadScene::Render()
{
	_transform->SetBuffer(0);
	_track->Render();
	_col->Render();

	_player->Render();
}

void CupHeadScene::PostRender()
{
	_player->PostRender();
}
