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

	// �����ϰ� ������ Ȥ�� �Ʒ������� ���� �մ� �۾�
	for (int y = 0; y < _poolCountY; ++y)
	{
		for (int x = 0; x < _poolCountX; ++x)
		{
			// ó�� ������ ��尡 �ƴ� ���
			if(x % 2 == 0 || y % 2 == 0)
				continue;

			// ������������ ������ Ȥ�� �Ʒ��� �� �ձ� ����
			if (x == _poolCountX - 2 && y == _poolCountY - 2)
			{
				continue;
			}

			// �������� ���� Ȥ�� �Ʒ��θ� �վ��� �� ���� �Ȼ���� �� ����ó��
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

			// �����ϰ� ������ Ȥ�� �Ʒ��� �� �ձ�
			const int randValue = rand() % 2;
			if(randValue == 0) // ������ ��ձ�
				_blocks[y][x + 1]->SetType(MazeBlock::BlockType::ABLE);
			else // �Ʒ��� ��ձ�
				_blocks[y + 1][x]->SetType(MazeBlock::BlockType::ABLE);
		}
	}
}

void Maze::CreateMazeByKruskal()
{
	// �� ���� ���� ����� �۾�
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

	// ��� ������ ���Ͽ� �̾����ִ� �������� ��������� �����ϰ� edges�� �߰�
	for (int y = 0; y < _poolCountY; y++)
	{
		for (int x = 0; x < _poolCountX; x++)
		{
			if(x % 2 == 0 || y % 2 == 0)
				continue;

			// ���������� �մ� �������� ���̸� ��������
			if (x < _poolCountX - 2)
			{
				const int randValue = rand() % 100;
				Edge_Kruskal edge;
				edge.cost = randValue;
				edge.u = Vector2(x,y);
				edge.v = Vector2(x + 2, y);
				edges.push_back(edge);
			}

			// �Ʒ������� �մ� �������� ���̸� ��������
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
	// �� ���� ���� ����� �۾�
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
			// ���� ��ġ�� ������ �ƴϸ� continue;
			if(x % 2 == 0 || y % 2 ==0)
				continue;

			// ��� ���� �ĺ����� ��Ƴ��� �۾�
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

	// �ش� ������ ���տ� ������ �Ǿ��ֳ�
	map<Vector2, bool> added;
	// �ش� ������ ������ ���� ����Ǿ� �ֳ�
	map<Vector2, Vector2> parent;
	// ����� �ִ� ���տ� ������ ���� ��, �ش� ������ ��� �ּ� ������ ����
	map<Vector2, int> best;

	// added, best �ʱ�ȭ
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

		// ���� ����� ����
		Vector2 here = bestEdge.v;

		// �̹� �߰��Ǿ������� ���h
		if(added[here])
			continue;

		added[here] = true;

		// �ʿ� ����
		int x = (parent[here].x + here.x) / 2;
		int y = (parent[here].y + here.y) / 2;
		_blocks[y][x]->SetType(MazeBlock::BlockType::ABLE);

		for (Edge& edge : edges[here])
		{
			if(added[edge.v])
			{
				continue;
			}

			// �ٸ� ��η� �� ���� �ĺ��� �߰��� �Ǿ������� ���h
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
