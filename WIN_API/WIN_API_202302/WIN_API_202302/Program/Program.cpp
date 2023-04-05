#include "framework.h"
#include "Program.h"

#include "../Scenes/PaintScene.h"
#include "../Scenes/LineScene.h"

Program::Program()
{
	_curScene = make_shared<LineScene>();
}

Program::~Program()
{
}

void Program::Update()
{
	_curScene->Update();
}

void Program::Render(HDC hdc)
{
	_curScene->Render(hdc);
}
