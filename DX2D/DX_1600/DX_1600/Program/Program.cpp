#include "framework.h"
#include "Program.h"

#include "../Scene/TutorialScene.h"

Program::Program()
{
	_curScene = make_shared<TutorialScene>();

	_view = make_shared<MatrixBuffer>();
	_projection = make_shared<MatrixBuffer>();

	XMMATRIX projectM = XMMatrixOrthographicOffCenterLH(0, WIN_WIDTH, 0, WIN_HEIGHT, 0.0f, 1.0f);

	_projection->SetData(projectM);

	_view->Update();
	_projection->Update();
}

Program::~Program()
{
}

void Program::Update()
{
	_curScene->Update();
}

void Program::Render()
{
	Device::GetInstance()->Clear();

	_view->SetVSBuffer(1);
	_projection->SetVSBuffer(2);
	_curScene->Render();

	Device::GetInstance()->Present();
}
