#include "framework.h"
#include "MazeRunner.h"

MazeRunner::MazeRunner(shared_ptr<Maze> maze)
: _maze(maze)
, _pos(maze->Start())
{
	// LeftHand();
	// DFS
	_visited = vector<vector<bool>>(maze->GetY(), vector<bool>(maze->GetX(),false));
	//BFS();
	// DFS({1,1});
	Dijkstra();
}

MazeRunner::~MazeRunner()
{
	_maze = nullptr;
}

void MazeRunner::Update()
{
	if(_pathIndex >= _path.size())
		return;

	_time += 0.3f;

	if (_time > 1.0f)
	{
		_time = 0.0f;
		_pos = _path[_pathIndex];

		if (_pathIndex > 0)
		{
			_maze->GetBlock(_path[_pathIndex - 1].y, _path[_pathIndex - 1].x)->SetType(MazeBlock::BlockType::FOOT_PRINT);
		}

		_pathIndex++;
	}

	_maze->GetBlock((int)_pos.y, (int)_pos.x)->SetType(MazeBlock::BlockType::PLAYER);
}

void MazeRunner::LeftHand()
{
	Vector2 pos = _pos; // 첫 시작 위치
	Vector2 endPos = _maze->End();
	_direction = Dir::DIR_UP;
	_path.push_back(pos);

	Vector2 frontPos[4] = 
	{
		Vector2(0,-1), // UP
		Vector2(1,0), // RIGHT
		Vector2(0,1), // Down
		Vector2(-1,0) // Left
	};

	while (pos != endPos)
	{
		// 현재 바라보는 방향 기준으로 왼쪽
		int newDir = (_direction - 1 + DIR_COUNT) % DIR_COUNT; // 좌측방향
		Vector2 oldDirVector2 = frontPos[_direction]; // 기존 방향
		Vector2 newDirVector2 = frontPos[newDir]; // 왼손 짚는 방향

		// 왼손이 가리키는 방향으로 전진할 수 있는지 확인
		Vector2 newGo = pos + newDirVector2;
		Vector2 oldGo = pos + oldDirVector2;
		if (Cango(newGo.y, newGo.x))
		{
			_direction = static_cast<Dir>(newDir);
			pos += newDirVector2;
			_maze->GetBlock(pos.y, pos.x)->SetType(MazeBlock::BlockType::VISITED);
			_path.push_back(pos);
		}

		// 현재 바라보는 방향으로 전진할 수 있는지 확인
		else if(Cango(oldGo.y, oldGo.x))
		{
			pos += oldDirVector2;
			_maze->GetBlock(pos.y, pos.x)->SetType(MazeBlock::BlockType::VISITED);
			_path.push_back(pos);
		}

		// 왼쪽쪽, 앞이 다 막혀있다면 시계방향으로 회전
		else
		{
			_direction = static_cast<Dir>((_direction + 1 + DIR_COUNT) % DIR_COUNT);
		}
	}

	stack<Vector2> s;

	for (int i = 0; i < _path.size() - 1; i++)
	{
		if(s.empty() == false && s.top() == _path[i + 1])
			s.pop();
		else
			s.push(_path[i]);
	}

	s.push(_path.back());
	_path.clear();

	while (true)
	{
		if(s.empty() == true)
			break;
		_path.push_back(s.top());
		s.pop();
	}

	std::reverse(_path.begin(), _path.end());
}

void MazeRunner::DFS(Vector2 here)
{
	if(_visited[(int)here.y][(int)here.x] == true)
		return;

	Vector2 endPos = _maze->End();
	if(_visited[endPos.y][endPos.x] == true)
		return;

	_visited[(int)here.y][(int)here.x] = true;
	_maze->GetBlock(here.y, here.x)->SetType(MazeBlock::BlockType::VISITED);
	_path.push_back(here);

	Vector2 frontPos[8] =
	{
		Vector2(0,-1), // UP
		Vector2(1,0), // RIGHT
		Vector2(0,1), // Down
		Vector2(-1,0), // Left
		Vector2(1,-1), // RightUp
		Vector2(1,1), // RightDown
		Vector2(-1,-1), // LeftUp
		Vector2(-1,1), // LeftDown
	};

	for (int i = 0; i < 8; i++)
	{
		Vector2 there = here + frontPos[i];

		if(_visited[there.y][there.x] == true)
			continue;

		if(Cango(there.y, there.x) == false)
			continue;

		DFS(there);
	}
}

void MazeRunner::BFS()
{
	Vector2 frontPos[8] =
	{
		Vector2(0,-1), // UP
		Vector2(1,0), // RIGHT
		Vector2(0,1), // Down
		Vector2(-1,0), // Left
		Vector2(1,-1), // RightUp
		Vector2(1,1), // RightDown
		Vector2(-1,-1), // LeftUp
		Vector2(-1,1), // LeftDown
	};

	Vector2 startPos = _maze->Start();
	Vector2 endPos = _maze->End();

	_discorvered = vector<vector<bool>>(_maze->GetY(), vector<bool>(_maze->GetX(), false));
	_parents = vector<vector<Vector2>>(_maze->GetY(), vector<Vector2>(_maze->GetX(), Vector2 (-1,-1)));

	queue<Vector2> q;
	q.push(startPos);
	_discorvered[startPos.y][startPos.x] = true;
	_parents[startPos.y][startPos.x] = startPos;

	while (true)
	{
		if(q.empty() == true)
			break;

		Vector2 here = q.front();
		if(_discorvered[endPos.y][endPos.x])
			break;

		q.pop();

		for (int i = 0; i < 8; i++)
		{
			Vector2 there = here + frontPos[i];

			if(_discorvered[there.y][there.x] == true)
				continue;

			if(Cango(there.y, there.x) == false)
				continue;

			q.push(there);
			_discorvered[there.y][there.x] = true;
			_parents[there.y][there.x] = here;
			_maze->GetBlock(there.y, there.x)->SetType(MazeBlock::BlockType::VISITED);
		}
	}

	Vector2 pos = endPos;
	_path.push_back(endPos);
	while (true)
	{
		if(pos == startPos)
			break;

		pos = _parents[pos.y][pos.x];
		_path.push_back(pos);
	}

	std::reverse(_path.begin(), _path.end());
}

void MazeRunner::Dijkstra()
{
	Vector2 frontPos[8] =
	{
		Vector2(0,-1), // UP
		Vector2(1,0), // RIGHT
		Vector2(0,1), // Down
		Vector2(-1,0), // Left
		Vector2(1,-1), // RightUp
		Vector2(1,1), // RightDown
		Vector2(-1,-1), // LeftUp
		Vector2(-1,1), // LeftDown
	};

	int Dijkstra_Dis[8] =
	{
		10,
		10,
		10,
		10,
		14,
		14,
		14,
		14,
	};

	Vector2 startPos = _maze->Start();
	Vector2 endPos = _maze->End();

	_best = vector<vector<int>>(_maze->GetY(), vector<int>(_maze->GetX(), INT_MAX));
	_parents = vector<vector<Vector2>>(_maze->GetY(), vector<Vector2>(_maze->GetX(), Vector2(-1, -1)));

	priority_queue<Vertex_Dijkstra, vector<Vertex_Dijkstra>, greater<Vertex_Dijkstra>> pq;

	Vertex_Dijkstra start;
	start.pos = _maze->Start();
	start.g = 0;
	pq.push(start);

	_best[start.pos.y][start.pos.x] = start.g;
	_parents[start.pos.y][start.pos.x] = start.pos;

	while (true)
	{
		if(pq.empty())
			break;

		Vector2 here = pq.top().pos;
		int cost = pq.top().g;
		pq.pop();

		for (int i = 0; i < 8; i++)
		{
			Vector2 there = here + frontPos[i];

			if(here == there)
				continue;

			if(Cango(there.y, there.x) == false)
				continue;

			int newCost = cost + Dijkstra_Dis[i];

			if(_best[there.y][there.x] < newCost)
				continue;

			if (there == _maze->End())
			{
				_parents[there.y][there.x] = here;
				break;
			}

			Vertex_Dijkstra thereV;
			thereV.pos = there;
			thereV.g = newCost;

			pq.push(thereV);
			_best[there.y][there.x] = newCost;
			_parents[there.y][there.x] = here;

			_maze->GetBlock(there.y, there.x)->SetType(MazeBlock::BlockType::VISITED);
		}
	}

	Vector2 pos = endPos;
	_path.push_back(endPos);
	while (true)
	{
		if (pos == startPos)
			break;

		pos = _parents[pos.y][pos.x];
		_path.push_back(pos);
	}

	std::reverse(_path.begin(), _path.end());

}

void MazeRunner::Astar()
{
	Vector2 frontPos[8] =
	{
		Vector2(0,-1), // UP
		Vector2(1,0), // RIGHT
		Vector2(0,1), // Down
		Vector2(-1,0), // Left
		Vector2(1,-1), // RightUp
		Vector2(1,1), // RightDown
		Vector2(-1,-1), // LeftUp
		Vector2(-1,1), // LeftDown
	};

	int Dijkstra_Dis[8] =
	{
		10,
		10,
		10,
		10,
		14,
		14,
		14,
		14,
	};

	Vector2 start = _maze->Start();
	Vector2 end = _maze->End();

	Vertex v;
	v.pos = start;
	v.g = 0;
	v.h = start.MahattanDistance(end);
	v.f = v.g + v.h;

	priority_queue<Vertex, vector<Vertex>, greater<Vertex>> pq;
	pq.push(v);

	_best[v.pos.y][v.pos.x] = v.f;
	_parents[v.pos.y][v.pos.x] = v.pos;

	while (true)
	{

	}
}

bool MazeRunner::Cango(int y, int x)
{
	if (_maze->GetBlockType(y, x) == MazeBlock::BlockType::DISABLE ||
		_maze->GetBlockType(y, x) == MazeBlock::BlockType::NONE)
	{
		return false;
	}
	return true;
}
