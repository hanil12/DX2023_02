#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

// �̻������ �׷���
// �׷����� ���� ����
// �׷����� ���
// �׷����� ���� ����

// �׷���
// ��峢�� ���þ��� ����Ǿ��ִ� ������ ��Ÿ�� �� ���� ������ �ڷᱸ��

vector<vector<int>> adjacent;
vector<vector<bool>> adjacent2;

// ���� ����Ʈ�� �׷����� �����ϱ�
void CreateGraph()
{
	// vector<int> v = vector<int>(6, -1);
	adjacent = vector<vector<int>>(7, vector<int>({}));

	adjacent[0].push_back(1);
	adjacent[0].push_back(2);
	adjacent[0].push_back(4);

	adjacent[1].push_back(0);

	adjacent[2].push_back(0);
	adjacent[2].push_back(3);
	adjacent[2].push_back(5);

	adjacent[3].push_back(2);

	adjacent[4].push_back(0);
	adjacent[4].push_back(6);

	adjacent[5].push_back(2);

	adjacent[6].push_back(4);
}

// ������ķ� �׷��� �����ϱ�
// ���� : Ž���ϴ� �ð��� ���
// ���� : �ʿ��� �����ͷ��� Ŀ����.
void CreateGraphByMatrix()
{
	adjacent2 = vector<vector<bool>>(7, vector<bool>(7, false));

	//	  0  1  2  3  4  5  6
	// 0  T  T  T  F  T  F  F
	// 1  T  T  F  F  F  F  F
	// 2  T  F  T  T  F  T  F
	// 3  F  F  T  T  F  F  F
	// 4  T  F  F  F  T  F  T
	// 5  F  F  T  F  F  T  F
	// 6  F  F  F  F  T  F  T

	adjacent2[0][0] = true;
	adjacent2[0][1] = true;
	adjacent2[0][2] = true;
	adjacent2[0][4] = true;

	adjacent2[1][0] = true;
	adjacent2[1][1] = true;

	adjacent2[2][0] = true;
	adjacent2[2][2] = true;
	adjacent2[2][3] = true;
	adjacent2[2][5] = true;

	adjacent2[3][2] = true;
	adjacent2[3][3] = true;

	adjacent2[4][0] = true;
	adjacent2[4][4] = true;
	adjacent2[4][6] = true;

	adjacent2[5][2] = true;
	adjacent2[5][5] = true;

	adjacent2[6][4] = true;
	adjacent2[6][6] = true;
}

int main()
{
#pragma region ��������Ʈ�� ����Ȯ���ϱ�
	CreateGraph();

	// Ȥ�� 0�� 1�� ���� ������ �Ǿ��ֽ��ϱ�?
	auto iter = std::find(adjacent[0].begin(), adjacent[0].end(), 1);
	if(iter != adjacent[0].end())
		cout << "���� �Ǿ��ֽ��ϴ�." << endl;
	else
		cout << "���� �Ǿ����� �ʽ��ϴ�." << endl;
#pragma endregion

	CreateGraphByMatrix();
	// 4 Vertex�� 6 Vertex�� ���� �������ֳ���?
	if(adjacent2[4][6])
		cout<<"4�� 6�� ����Ǿ��ֽ��ϴ�."<<endl;
	else
		cout<<"4�� 6�� ���� �ȵǾ��ֽ��ϴ�."<<endl;

	return 0;
}