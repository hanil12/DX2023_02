#include "framework.h"
#include "EffectScene.h"

EffectScene::EffectScene()
{
	EffectManager::GetInstance()->AddEffect("Hit", L"Resource/CupHead/hit_4x2.png", Vector2(4,2), Vector2(150,150), 0.1f);

}

EffectScene::~EffectScene()
{
}

void EffectScene::Update()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		EFFECT_PLAY("Hit", MOUSE_POS);
	}
}

void EffectScene::Render()
{

}
