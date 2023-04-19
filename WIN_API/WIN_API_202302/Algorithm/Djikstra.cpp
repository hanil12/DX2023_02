#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

// Djikstra Algorithm : 길찾기 알고리즘

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

		// pq에서 빼고 연결된 지점 방문하기 전에, 이미 더 좋은 best가 있었으면 그냥 pq에서 빼기만
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

			// 나중에 방문할려 했는데 이미 좋은 값이 있었다.
			if(nextCost >= best[there])
				continue;

			// 방문
			Vertex v = Vertex(there, nextCost);
			pq.push(v);
			best[there] = nextCost;
			discovered[there] = true;
			parent[there] = here;
		}
	}

	for (int i = 0; i < adjacent2.size(); i++)
	{
		cout << i << "의 부모는 " << parent[i] << endl;
		cout << i << "까지의 최단거리는 " << best[i] << endl;
	}
}

int main()
{
	CreateGraphByMatrix();
	Djikstra(0);

}