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
// => 분할 정복 패러다임(Divide And Conquer)
// - 분할 : 문제를 최대한 단순하게 분할한다.
// - 정복 : 문제를 해결한다.
// - 결합 : 결과를 취합하여 마무리한다.

// => 폰노이만이 개발한 알고리즘

// Quick, Merge, Heap
// 평균적으로 N * log2N 시간 복잡도

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

	// 왼쪽이 먼저 끝남
	if (leftIndex > mid)
	{
		while (rightIndex <= right)
		{
			temp.push_back(v[rightIndex]);
			rightIndex++;
		}
	}

	// 오른쪽이 먼저 끝남
	if (rightIndex > right)
	{
		while (leftIndex <= mid)
		{
			temp.push_back(v[leftIndex]);
			leftIndex++;
		}
	}

	// temp에 넣은 원소들을 v에 복사
	for (int i = 0; i < temp.size(); i++)
	{
		v[left + i] = temp[i];
	}
}

void MergeSort(vector<int>& v, int left, int right)
{
	if(left >= right)
		return;

	// 분할
	int mid = (left + right) / 2;
	MergeSort(v, left, mid);
	MergeSort(v, mid + 1, right);

	// 정복 결합
	MergeResult(v,left,mid,right);
}

int main()
{
	vector<int> v = {55, 30, 15, 100, 1, 5 ,70, 30};

	MergeSort(v, 0, 7);

	return 0;
}