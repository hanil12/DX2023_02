#include "framework.h"
#include "CupHeadScene.h"

#include "../../Object/CupHead/Cup_Player.h"
#include "../../Object/CupHead/Cup_Boss.h"

CupHeadScene::CupHeadScene()
{
#pragma region CupHead
	_player = make_shared<Cup_Player>();
	_player->SetPosition(Vector2(0,0));

	_boss = make_shared<Cup_Boss>();

	_track = make_shared<Quad>(L"Resource/CupHead/track.png");
	_transform = make_shared<Transform>();
	Vector2 trackSize = _track->GetQuadHalfSize();
	_col = make_shared<RectCollider>(trackSize * 2.0f);

	_transform->SetParent(_col->GetTransform());
	_transform->SetPosition(Vector2(0,75));

	Vector2 pos = CENTER;
	pos.y -= 350.0f;
	_col->GetTransform()->SetPosition(Vector2(0.0f, CENTER.y * - 1));

	CAMERA->SetTarget(_player->GetTransform());
	CAMERA->SetLeftBottom(Vector2(-trackSize.x, -1000.0f));
	CAMERA->SetRightTop(Vector2(trackSize.x, 1000.0f));

	shared_ptr<SRV> srv = ADD_SRV(L"Resource/UI/Button.png");
	_button = make_shared<Button>(L"Resource/UI/Button.png", srv->GetImageSize());
	_button->SetPosition(Vector2(0,0));
	_button->SetEvent(std::bind(&CupHeadScene::Load, this));

	Load();
#pragma endregion

#pragma region RTV
	_rtv = make_shared<RenderTarget>();
	_rtvQuad = make_shared<Quad>(Vector2(WIN_WIDTH, WIN_HEIGHT));
	_rtvQuad->SetSRV(_rtv->GetSRV());
	_rtvQuad->SetPS(ADD_PS(L"Shader/FilterPS.hlsl"));

	// rtvQuad Transform
	_rtvTransform = make_shared<Transform>();
	_rtvTransform->SetPosition(Vector2(-50,-100));
	_rtvTransform->SetScale(Vector2(0.5f,0.5f));

	// fiterBuffer
	_filter = make_shared<FilterBuffer>();
	_filter->_data.selected = 1;

#pragma endregion
}

CupHeadScene::~CupHeadScene()
{
}

void CupHeadScene::Init()
{
	Load();
}

void CupHeadScene::End()
{
	// CupHead ÃÑ¾ËÈ¸¼ö...
}

void CupHeadScene::Update()
{
	_player->Update();
	_boss->Update();

	_transform->Update();
	_col->Update();

	_button->Update();

	if(_col->Block(_player->GetCollider()))
		_player->SetGrounded();

	_rtvTransform->Update();
	_filter->Update();
}

void CupHeadScene::Render()
{
	_rtvTransform->SetBuffer(0);
	_filter->SetPSBuffer(0);
	_rtvQuad->Render();
}

void CupHeadScene::PreRender()
{
	_rtv->Set();

	_transform->SetBuffer(0);
	_track->Render();
	_col->Render();

	_player->Render();
	_boss->Render();
}

void CupHeadScene::PostRender()
{
	_player->PostRender();
	_boss->PostRender();

	if (ImGui::Button("TargetON", ImVec2(100, 50)))
	{
		CAMERA->SetTarget(_player->GetTransform());
	}
	
	if (ImGui::Button("TargetOFF", ImVec2(100, 50)))
	{
		CAMERA->SetTarget(nullptr);
	}

	if (ImGui::Button("Save", ImVec2(100, 50)))
	{
		Save();
	}

	if (ImGui::Button("Load", ImVec2(100, 50)))
	{
		Load();
	}

	ImGui::SliderInt("Mosaic", &_filter->_data.value1,1, 300);

	_button->PostRender();
}

void CupHeadScene::Save()
{
	BinaryWriter writer = BinaryWriter(L"Save/test.test");
	writer.Int(1);

	Vector2 playerPos = _player->GetCollider()->GetTransform()->GetWorldPosition();

	writer.String("PlayerPos");
	writer.Byte(&playerPos, sizeof(Vector2));
}

void CupHeadScene::Load()
{
	BinaryReader reader = BinaryReader(L"Save/test.test");
	int temp = reader.Int();

	string str = reader.String();
	assert(str == "PlayerPos");

	Vector2 playerPos;
	Vector2* ptr = &playerPos;
	reader.Byte((void**)&ptr, sizeof(Vector2));

	_player->SetPosition(playerPos);
}
