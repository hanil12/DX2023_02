#include "framework.h"
#include "Program.h"

#include "../Scene/TutorialScene.h"

Program::Program()
{
	_curScene = make_shared<TutorialScene>();
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

	_curScene->Render();

	Device::GetInstance()->Present();
}
