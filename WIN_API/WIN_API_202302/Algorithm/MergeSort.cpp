#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

// MergeSort / StableSort
// => ���� ���� �з�����(Divide And Conquer)
// - ���� : ������ �ִ��� �ܼ��ϰ� �����Ѵ�.
// - ���� : ������ �ذ��Ѵ�.
// - ���� : ����� �����Ͽ� �������Ѵ�.

// => �����̸��� ������ �˰���

// Quick, Merge, Heap
// ��������� N * log2N �ð� ���⵵

void MergeResult(vector<int>& v,int left,int mid,int right)
{
	int leftIndex = left;
	int rightIndex = mid + 1;

	vector<int> temp;

	while (true)
	{
		if(leftIndex > mid || rightIndex > right)
			break;

		if (v[leftIndex] <= v[rightIndex])
		{
			temp.push_back(v[leftIndex]);
			leftIndex++;
		}
		else
		{
			temp.push_back(v[rightIndex]);
			rightIndex++;
		}
	}

	// ������ ���� ����
	if (leftIndex > mid)
	{
		while (rightIndex <= right)
		{
			temp.push_back(v[rightIndex]);
			rightIndex++;
		}
	}

	// �������� ���� ����
	if (rightIndex > right)
	{
		while (leftIndex <= mid)
		{
			temp.push_back(v[leftIndex]);
			leftIndex++;
		}
	}

	// temp�� ���� ���ҵ��� v�� ����
	for (int i = 0; i < temp.size(); i++)
	{
		v[left + i] = temp[i];
	}
}

void MergeSort(vector<int>& v, int left, int right)
{
	if(left >= right)
		return;

	// ����
	int mid = (left + right) / 2;
	MergeSort(v, left, mid);
	MergeSort(v, mid + 1, right);

	// ���� ����
	MergeResult(v,left,mid,right);
}

int main()
{
	vector<int> v = {55, 30, 15, 100, 1, 5 ,70, 30};

	MergeSort(v, 0, 7);

	return 0;
}