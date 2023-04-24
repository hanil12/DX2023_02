#pragma once
#include "../framework.h"

class DisJointSet
{
public:
	DisJointSet(int n)
	{
		_parent.resize(n, 0);
		_rank.resize(n, 1);

		for (int i = 0; i < n; i++)
		{
			_parent[i] = i;
		}
	}

	int FindLeader(int u)
	{
		if (u == _parent[u])
			return u;

		int parent = _parent[u];

		return FindLeader(parent);
	}

	void Merge(int u, int v)
	{
		int leaderU = FindLeader(u);
		int leaderV = FindLeader(v);

		if (leaderU == leaderV)
			return;

		if (_rank[leaderU] > _rank[leaderV])
		{
			std::swap(leaderU, leaderV);
		}

		_parent[leaderU] = leaderV;

		if (_rank[leaderU], _rank[leaderV])
			_rank[leaderV]++;
	}

private:
	vector<int> _parent;
	vector<int> _rank;
};