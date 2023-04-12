#pragma once
class Maze
{
public:
	Maze();
	~Maze();

	void Update();
	void Render(HDC hdc);

	void CreateMaze();

	Vector2 Start() { return Vector2(1,1); }
	Vector2 End() {return Vector2(int(_poolCountY - 2), int(_poolCountX - 2)); }
	MazeBlock::BlockType GetBlockType(int y, int x); 
	shared_ptr<MazeBlock> GetBlock(int y, int x) { return _blocks[y][x]; }

private:
	vector<vector<shared_ptr<MazeBlock>>> _blocks;
	UINT _poolCountX = 25;
	UINT _poolCountY = 25;
};

