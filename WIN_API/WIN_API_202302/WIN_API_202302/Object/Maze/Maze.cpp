#include "framework.h"
#include "Maze.h"

Maze::Maze()
{
	_blocks.reserve(_poolCountY);
	Vector2 offset = {400,150};
	for (int y = 0; y < _poolCountY; y++)
	{
		vector<shared_ptr<MazeBlock>> blocksX;
		blocksX.reserve(_poolCountX);
		for (int x = 0; x < _poolCountX; x++)
		{
			shared_ptr<MazeBlock> block = make_shared<MazeBlock>();
			block->SetType(MazeBlock::BlockType::DISABLE);
			Vector2 distance = {17 * x,17 * y};
			block->SetPosition(offset + distance);
			blocksX.push_back(block);
		}
		_blocks.push_back(blocksX);
	}

	CreateMazeByPrim();

	_blocks[1][1]->SetType(MazeBlock::BlockType::START);
	_blocks[_poolCountY - 2][_poolCountX - 2]->SetType(MazeBlock::BlockType::END);
}

Maze::~Maze()
{
}

void Maze::Update()
{
	for (auto blocksX : _blocks)
	{
		for (auto block : blocksX)
		{
			block->Update();
		}
	}
}

void Maze::Render(HDC hdc)
{
	for (auto blocksX : _blocks)
	{
		for (auto block : blocksX)
		{
			block->Render(hdc);
		}
	}
}

// Maze for Programmers
void Maze::CreateMaze()
{
	for (int y = 0; y < _poolCountY; ++y)
	{
		for (int x = 0; x < _poolCountX; ++x)
		{
			if (x % 2 == 0 || y % 2 == 0)
				_blocks[y][x]->SetType(MazeBlock::BlockType::DISABLE);
			else
				_blocks[y][x]->SetType(MazeBlock::BlockType::ABLE);
		}
	}

	// 랜덤하게 오른쪽 혹은 아래쪽으로 길을 뚫는 작업
	for (int y = 0; y < _poolCountY; ++y)
	{
		for (int x = 0; x < _poolCountX; ++x)
		{
			// 처음 설정한 노드가 아닌 경우
			if(x % 2 == 0 || y % 2 == 0)
				continue;

			// 끝지점에서는 오른쪽 혹은 아래쪽 길 뚫기 중지
			if (x == _poolCountX - 2 && y == _poolCountY - 2)
			{
				continue;
			}

			// 랜덤으로 우측 혹은 아래로만 뚫었을 때 길이 안생기는 것 예외처리
			if (y == _poolCountY - 2)
			{
				_blocks[y][x + 1]->SetType(MazeBlock::BlockType::ABLE);
				continue;
			}

			if (x == _poolCountX - 2)
			{
				_blocks[y + 1][x]->SetType(MazeBlock::BlockType::ABLE);
				continue;
			}

			// 랜덤하게 오른쪽 혹은 아래쪽 길 뚫기
			const int randValue = rand() % 2;
			if(randValue == 0) // 오른쪽 길뚫기
				_blocks[y][x + 1]->SetType(MazeBlock::BlockType::ABLE);
			else // 아래쪽 길뚫기
				_blocks[y + 1][x]->SetType(MazeBlock::BlockType::ABLE);
		}
	}
}

void Maze::CreateMazeByKruskal()
{
	// 각 이을 정점 만드는 작업
	for (int y = 0; y < _poolCountY; ++y)
	{
		for (int x = 0; x < _poolCountX; ++x)
		{
			if (x % 2 == 0 || y % 2 == 0)
				_blocks[y][x]->SetType(MazeBlock::BlockType::DISABLE);
			else
				_blocks[y][x]->SetType(MazeBlock::BlockType::ABLE);
		}
	}

	vector<Edge_Kruskal> edges;

	// 모든 정점에 대하여 이어져있는 간선들을 랜덤밸류로 설정하고 edges에 추가
	for (int y = 0; y < _poolCountY; y++)
	{
		for (int x = 0; x < _poolCountX; x++)
		{
			if(x % 2 == 0 || y % 2 == 0)
				continue;

			// 오른쪽으로 잇는 간선들의 길이를 랜덤으로
			if (x < _poolCountX - 2)
			{
				const int randValue = rand() % 100;
				Edge_Kruskal edge;
				edge.cost = randValue;
				edge.u = Vector2(x,y);
				edge.v = Vector2(x + 2, y);
				edges.push_back(edge);
			}

			// 아래쪽으로 잇는 간선들의 길이를 랜덤으로
			if (y < _poolCountY - 2)
			{
				const int randValue = rand() % 100;
				Edge_Kruskal edge;
				edge.cost = randValue;
				edge.u = Vector2(x,y);
				edge.v = Vector2(x,y + 2);
				edges.push_back(edge);
			}
		}
	}

	std::sort(edges.begin(), edges.end(), [](const Edge_Kruskal& a, const Edge_Kruskal& b)-> bool 
	{ return a.cost < b.cost; });

	DisJointSet sets(_poolCountX * _poolCountY);

	for (auto edge : edges)
	{
		int u = edge.u.x + edge.u.y * _poolCountY;
		int v = edge.v.x + edge.v.y * _poolCountY;

		if(sets.FindLeader(u) == sets.FindLeader(v))
			continue;

		sets.Merge(u,v);
		int edgeX = (edge.u.x + edge.v.x) / 2;
		int edgeY = (edge.u.y + edge.v.y) / 2;

		_blocks[edgeY][edgeX]->SetType(MazeBlock::BlockType::ABLE);
	}
}

void Maze::CreateMazeByPrim()
{
	// 각 이을 정점 만드는 작업
	for (int y = 0; y < _poolCountY; ++y)
	{
		for (int x = 0; x < _poolCountX; ++x)
		{
			if (x % 2 == 0 || y % 2 == 0)
				_blocks[y][x]->SetType(MazeBlock::BlockType::DISABLE);
			else
				_blocks[y][x]->SetType(MazeBlock::BlockType::ABLE);
		}
	}

	//// edges[Vector2(1,1)] ... 
	map<Vector2, vector<Edge>> edges;
	for (int y = 0; y < _poolCountY; y++)
	{
		for (int x = 0; x < _poolCountX; x++)
		{
			// 현재 위치가 정점이 아니면 continue;
			if(x % 2 == 0 || y % 2 ==0)
				continue;

			// 모든 간선 후보들을 담아놓는 작업
			if (x < _poolCountX - 2)
			{
				const int randValue = rand() % 100;
				Vector2 u = Vector2(x,y);
				Vector2 v = Vector2(x + 2, y);
				edges[u].push_back({v, randValue});
				edges[v].push_back({u, randValue});
			}

			if (y < _poolCountY - 2)
			{
				const int randValue = rand() % 100;
				Vector2 u = Vector2(x,y);
				Vector2 v = Vector2(x, y + 2);
				edges[u].push_back({v, randValue});
				edges[v].push_back({u, randValue});
			}
		}
	}

	// 해당 정점이 집합에 포함이 되어있나
	map<Vector2, bool> added;
	// 해당 정점이 누구에 의해 연결되어 있나
	map<Vector2, Vector2> parent;
	// 만들고 있는 집합에 인접한 간선 중, 해당 정점에 닿는 최소 간선의 정보
	map<Vector2, int> best;

	// added, best 초기화
	for (int y = 0; y < _poolCountY; y++)
	{
		for (int x = 0; x < _poolCountX; x++)
		{
			best[Vector2(x,y)] = INT_MAX;
			added[Vector2(x,y)] = false;
		}
	}

	priority_queue<Edge> pq;
	Vector2 startPos = {1,1};
	pq.push(Edge{startPos, 0});
	best[startPos] = 0;
	parent[startPos] = startPos;

	while (true)
	{
		if(pq.empty())
			break;

		Edge bestEdge = pq.top();
		pq.pop();

		// 새로 연결될 정점
		Vector2 here = bestEdge.v;

		// 이미 추가되어있으면 스킾
		if(added[here])
			continue;

		added[here] = true;

		// 맵에 적용
		int x = (parent[here].x + here.x) / 2;
		int y = (parent[here].y + here.y) / 2;
		_blocks[y][x]->SetType(MazeBlock::BlockType::ABLE);

		for (Edge& edge : edges[here])
		{
			if(added[edge.v])
			{
				continue;
			}

			// 다른 경로로 더 좋은 후보가 발견이 되어있으면 스킾
			if (edge.cost > best[edge.v])
			{
				continue;
			}

			best[edge.v] = edge.cost;
			parent[edge.v] = here;
			pq.push(edge);
		}
	}
}

MazeBlock::BlockType Maze::GetBlockType(int y, int x)
{
	if(y < 0 || y > _poolCountY)
		return MazeBlock::BlockType::NONE;
	if(x < 0 || x > _poolCountX)
		return MazeBlock::BlockType::NONE;

	return _blocks[y][x]->GetType();
}
