#include "framework.h"
#include "LineScene.h"

LineScene::LineScene()
{
	_lineFloor = make_shared<Line>(Vector2(0,500), Vector2(1000,500)); // 검은색선, 3
	_lineMouse = make_shared<Line>(Vector2(50, 250), Vector2(50, 250)); // 파란색선, 3
	_lineShadow = make_shared <Line>(Vector2(50, 450), Vector2(60, 450)); // 빨간선, 3
}

LineScene::~LineScene()
{
}

void LineScene::Update()
{
	_lineMouse->_end = mousePos;

	_lineFloor->Update();
	_lineMouse->Update();
	_lineShadow->Update();
}

void LineScene::Render(HDC hdc)
{
	_lineFloor->Render(hdc);
	_lineMouse->Render(hdc);
	_lineShadow->Render(hdc);
}
