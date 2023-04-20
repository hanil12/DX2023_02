#pragma once
class MazeRunner
{
public:
	struct Vertex_Dijkstra
	{
		Vector2 pos;
		int g;

		bool operator<(const Vertex_Dijkstra& other) const
		{
			return this->g < other.g;
		}

		bool operator>(const Vertex_Dijkstra& other) const
		{
			return this->g > other.g;
		}
	};

	struct Vertex
	{
		Vector2 pos;
		int g = 0;
		int h = 0;
		int f = 0;

		bool operator<(const Vertex& other) const
		{
			return this->f < other.f;
		}

		bool operator>(const Vertex& other) const
		{
			return this->f > other.f;
		}
	};

	MazeRunner(shared_ptr<Maze> maze);
	~MazeRunner();

	void Update();

	void LeftHand();
	void DFS(Vector2 start);
	void BFS();
	void Dijkstra();
	void Astar();

	bool Cango(int y, int x);

private:
	shared_ptr<Maze> _maze;

	Vector2 _pos;
	Dir _direction = Dir::DIR_UP;

	vector<Vector2> _path;
	int _pathIndex = 0;
	float _time = 0.0f;

	// DFS
	vector<vector<bool>> _visited;

	// BFS
	vector<vector<bool>> _discorvered;
	vector<vector<Vector2>> _parents;

	// Dijkstra
	vector<vector<int>> _best;
};

