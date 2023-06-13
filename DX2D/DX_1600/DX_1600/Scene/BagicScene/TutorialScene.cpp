#include "framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
	_quad1 = make_shared<Quad>(L"Resource/Zelda.png");
	_quad1->SetPS(ADD_PS(L"Shader/FilterPS.hlsl"));
	_transform1 = make_shared<Transform>();

	_transform1->SetPosition(CENTER);

	_filterBuffer = make_shared<FilterBuffer>();
	_filterBuffer->_data.imageSize = _quad1->GetImageSize();
}

TutorialScene::~TutorialScene()
{
}

void TutorialScene::Update()
{
	_transform1->Update();
	_filterBuffer->Update();
}

void TutorialScene::Render()
{
	_transform1->SetBuffer(0);
	_filterBuffer->SetPSBuffer(0);
	_quad1->Render();
}

void TutorialScene::PostRender()
{
	ImGui::SliderInt("Selected", &_filterBuffer->_data.selected, 0,10);
	ImGui::SliderInt("value1", &_filterBuffer->_data.value1, 1, 300);
	ImGui::SliderInt("value2", &_filterBuffer->_data.value2, 0, 300);
}
