#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

// Djikstra Algorithm : ��ã�� �˰���

using namespace std;

vector<vector<int>> adjacent2;
vector<bool> discovered;
vector<int> parent;
vector<int> best;

void CreateGraphByMatrix()
{
	adjacent2 = vector<vector<int>>(7, vector<int>(7, -1));
	discovered = vector<bool>(7, false);
	parent = vector<int>(7, -1);

	adjacent2[0][0] = 0;
	adjacent2[0][1] = 15;
	adjacent2[0][2] = 3;
	adjacent2[0][4] = 10;

	adjacent2[1][0] = 15;
	adjacent2[1][1] = 0;


	adjacent2[2][0] = 3;
	adjacent2[2][2] = 0;
	adjacent2[2][3] = 4;
	adjacent2[2][4] = 5;
	adjacent2[2][5] = 2;

	adjacent2[3][2] = 4;
	adjacent2[3][3] = 0;

	adjacent2[4][0] = 10;
	adjacent2[4][2] = 5;
	adjacent2[4][4] = 0;
	adjacent2[4][6] = 7;

	adjacent2[5][2] = 2;
	adjacent2[5][5] = 0;

	adjacent2[6][4] = 7;
	adjacent2[6][6] = 0;
}

struct Vertex
{
	Vertex(int num, int g): vertexNum(num), g(g) { }

	bool operator<(const Vertex& other) const
	{
		return g < other.g;
	}

	bool operator>(const Vertex& other) const
	{
		return g > other.g;
	}

	int vertexNum;
	int g;
};

void Djikstra(int start)
{
	best = vector<int>(adjacent2.size(), INT_MAX);
	priority_queue<Vertex, vector<Vertex>, greater<Vertex>> pq;
	Vertex startV = Vertex(0, 0);
	pq.push(startV);
	best[startV.vertexNum] = startV.g;

	discovered[startV.vertexNum] = true;
	parent[startV.vertexNum] = startV.vertexNum;

	while (true)
	{
		if(pq.empty())
			break;

		int cost = pq.top().g;
		int here = pq.top().vertexNum;
		pq.pop();

		// pq���� ���� ����� ���� �湮�ϱ� ����, �̹� �� ���� best�� �־����� �׳� pq���� ���⸸
		if (best[here] < cost)
		{
			cout << here << endl;
			cout << cost << endl;
			cout << best[here] << endl;
		}

		for (int there = 0; there < adjacent2.size(); there++)
		{
			if(here == there)
				continue;
			if(adjacent2[here][there] == -1)
				continue;

			int nextCost = best[here] + adjacent2[here][there];

			// ���߿� �湮�ҷ� �ߴµ� �̹� ���� ���� �־���.
			if(nextCost >= best[there])
				continue;

			// �湮
			Vertex v = Vertex(there, nextCost);
			pq.push(v);
			best[there] = nextCost;
			discovered[there] = true;
			parent[there] = here;
		}
	}

	for (int i = 0; i < adjacent2.size(); i++)
	{
		cout << i << "�� �θ�� " << parent[i] << endl;
		cout << i << "������ �ִܰŸ��� " << best[i] << endl;
	}
}

int main()
{
	CreateGraphByMatrix();
	Djikstra(0);

}