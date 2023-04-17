#include "framework.h"
#include "MazeRunner.h"

MazeRunner::MazeRunner(shared_ptr<Maze> maze)
: _maze(maze)
, _pos(maze->Start())
{
	// LeftHand();
	// DFS
	_visited = vector<vector<bool>>(maze->GetY(), vector<bool>(maze->GetX(),false));
	DFS(_pos);
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
			_path.push_back(pos);
		}

		// 현재 바라보는 방향으로 전진할 수 있는지 확인
		else if(Cango(oldGo.y, oldGo.x))
		{
			pos += oldDirVector2;
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
	_path.push_back(here);

	Vector2 frontPos[4] =
	{
		Vector2(0,-1), // UP
		Vector2(1,0), // RIGHT
		Vector2(0,1), // Down
		Vector2(-1,0) // Left
	};

	for (int i = 0; i < 4; i++)
	{
		Vector2 there = here + frontPos[i];

		if(_visited[there.y][there.x] == true)
			continue;

		if(Cango(there.y, there.x) == false)
			continue;

		DFS(there);
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
