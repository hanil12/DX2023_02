#include "framework.h"
#include "SpriteScene.h"

SpriteScene::SpriteScene()
{
	_sprite = make_shared<Sprite>(L"Resource/zelda_sprite.png", Vector2(10,8), Vector2(100,100));
	_transform = make_shared<Transform>();
	_transform->SetPosition(CENTER);
}

SpriteScene::~SpriteScene()
{
}

void SpriteScene::Update()
{
	_transform->Update();
	_sprite->Update();
}

void SpriteScene::Render()
{
	_transform->SetBuffer(0);
	_sprite->Render();
}

void SpriteScene::PostRender()
{
	ImGui::SliderFloat2("Current Frame", (float*)&_curFrame, 0, 10, "%.0f");
	_sprite->SetCurFrame(_curFrame);
}
