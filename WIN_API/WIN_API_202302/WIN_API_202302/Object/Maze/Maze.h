#pragma once
class Maze
{
public:
	Maze();
	~Maze();

	void Update();
	void Render(HDC hdc);

	void CreateMaze();

private:
	vector<vector<shared_ptr<MazeBlock>>> _blocks;
	UINT _poolCountX = 25;
	UINT _poolCountY = 25;
};

