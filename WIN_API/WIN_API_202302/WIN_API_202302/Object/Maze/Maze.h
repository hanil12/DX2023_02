#pragma once
class Maze
{
public:
	struct Edge
	{
		Vector2 u;
		Vector2 v;
		int cost;
	};

	Maze();
	~Maze();

	void Update();
	void Render(HDC hdc);

	void CreateMaze();
	void CreateMazeByKruskal();

	Vector2 Start() { return Vector2(1,1); }
	Vector2 End() {return Vector2(int(_poolCountY - 2), int(_poolCountX - 2)); }
	MazeBlock::BlockType GetBlockType(int y, int x); 
	shared_ptr<MazeBlock> GetBlock(int y, int x) { return _blocks[y][x]; }

	UINT GetX() { return _poolCountX; }
	UINT GetY() { return _poolCountY; }

private:
	vector<vector<shared_ptr<MazeBlock>>> _blocks;
	UINT _poolCountX = 25;
	UINT _poolCountY = 25;
};

