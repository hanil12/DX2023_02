#include "framework.h"
#include "Program.h"

#include "../Scene/BagicScene/TutorialScene.h"
#include "../Scene/BagicScene/SolarSystem.h"
#include "../Scene/BagicScene/DungreedScene.h"
#include "../Scene/BagicScene/ColliderScene.h"
#include "../Scene/BagicScene/SpriteScene.h"
#include "../Scene/BagicScene/ActionScene.h"
#include "../Scene/BagicScene/CupHeadScene.h"

Program::Program() 
{
	srand(static_cast<unsigned int>(time(nullptr)));

	_curScene = make_shared<CupHeadScene>();

	_view = make_shared<MatrixBuffer>();
	_projection = make_shared<MatrixBuffer>();

	XMMATRIX projectM = XMMatrixOrthographicOffCenterLH(0, WIN_WIDTH, 0, WIN_HEIGHT, 0.0f, 1.0f);

	_projection->SetData(projectM);

	_view->Update();
	_projection->Update();

	Timer::GetInstance()->SetLockFPS(60.0);
}

Program::~Program()
{
}

void Program::Update()
{
	InputManager::GetInstance()->Update();
	Timer::GetInstance()->Update();

	_curScene->Collider_Update();
	_curScene->Update();
}

void Program::Render()
{
	Device::GetInstance()->Clear();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	_view->SetVSBuffer(1);
	_projection->SetVSBuffer(2);

	ALPHA->SetState();

	_curScene->Render();

	ImGui::Text("FPS : %d", Timer::GetInstance()->GetFPS());
	ImGui::Text("MousePos : { %.0f , %.0f}", MOUSE_POS.x, MOUSE_POS.y);

	_curScene->PostRender();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Device::GetInstance()->Present();
}
