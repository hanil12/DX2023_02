#include "framework.h"
#include "Program.h"

#include "../Scene/BagicScene/TutorialScene.h"
#include "../Scene/BagicScene/SolarSystem.h"
#include "../Scene/BagicScene/DungreedScene.h"
#include "../Scene/BagicScene/ColliderScene.h"
#include "../Scene/BagicScene/SpriteScene.h"
#include "../Scene/BagicScene/ActionScene.h"
#include "../Scene/BagicScene/CupHeadScene.h"
#include "../Scene/BagicScene/EffectScene.h"

Program::Program() 
{
	srand(static_cast<unsigned int>(time(nullptr)));

	_curScene = make_shared<CupHeadScene>();

	Timer::GetInstance()->SetLockFPS(60.0);
}

Program::~Program()
{
}

void Program::Update()
{
	InputManager::GetInstance()->Update();
	Timer::GetInstance()->Update();
	Sound::GetInstance()->Update();
	CAMERA->Update();

	_curScene->Collider_Update();
	_curScene->Update();

	EffectManager::GetInstance()->Update();
}

void Program::Render()
{
	Device::GetInstance()->Clear();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	CAMERA->SetCameraBuffer();
	CAMERA->SetProjectionBuffer();

	ALPHA->SetState();

	_curScene->Render();
	EffectManager::GetInstance()->Render();

	ImGui::Text("FPS : %d", Timer::GetInstance()->GetFPS());
	ImGui::Text("MousePos : { %.0f , %.0f}", MOUSE_POS.x, MOUSE_POS.y);

	CAMERA->PostRender();
	_curScene->PostRender();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Device::GetInstance()->Present();
}
