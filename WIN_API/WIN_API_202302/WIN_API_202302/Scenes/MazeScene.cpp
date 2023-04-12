#include "framework.h"
#include "MazeScene.h"

MazeScene::MazeScene()
{
	_maze = make_shared<Maze>();
	_runner = make_shared<MazeRunner>(_maze);
}

MazeScene::~MazeScene()
{
}

void MazeScene::Update()
{
	_maze->Update();
	_runner->Update();
}

void MazeScene::Render(HDC hdc)
{
	_maze->Render(hdc);
}
