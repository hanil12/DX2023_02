#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

// LIS (Longest Increasing Sequence)
// �κ� ���� �������� ���� �� ���� ���̸� ã�´�.
// Seq : 1 2 9 5 8 10

// �κ� ���� : ������ �����ϵ�, �������� ���� ���� �ִ�.
// 1 2 5 (O)
// 1 2 9 8 (O)
// 2 9 1 (X)

// �κ� ���� ���� : �κ� �����̸鼭 ���� �����Ǵ� ������ �����Ǵ� ����
// 1 2 5 (O)
// 1 2 9 8 (X)

vector<int> seq = {1,2,3,4,3,4,5,6};

// LIS(5) : 1
// LIS(4) : LIS(5) or LIS(5) + 1
// LIS(3) : LIS(4) or LIS(4) + 1
// LIS(2) : LIS(3) or LIS(3) + 1
// LIS(1) : LIS(2) or LIS(2) + 1
// LIS(0) : LIS(1) or LIS(1) + 1 => 4

vector<int> cache = vector<int>(100, -1);

int LIS(int pos)
{
	// ����
	if(pos == seq.size() - 1)
		return 1;

	// ĳ��
	int& ref = cache[pos];

	// ���ϱ�
	ref = 1;
	for (int next = pos + 1; next < seq.size(); next++)
	{
		if (seq[pos] <= seq[next])
		{
			ref = max(ref, LIS(next) + 1);
		}
	}

	return ref;
}

int myLis(int pos)
{
	if(pos == seq.size() - 1)
		return 1;

	int& ref = cache[pos];

	if(ref != -1)
		return ref;

	int maxLis = 0;
	int index = pos + 1;

	for (int i = pos + 1; i < seq.size(); i++)
	{
		if (maxLis <= LIS(i))
		{
			if (seq[i] <= seq[index])
			{
				index = i;
			}

			maxLis = LIS(i);
		}
	}

	if(seq[pos] < seq[index] || (index - pos) > maxLis)
		ref = maxLis + 1;
	else
		ref = maxLis;

	return ref;
}

int main()
{
	int lis = 0;

	for (int i = 0; i < seq.size(); i++)
	{
		lis = max(lis, LIS(i));
	}

	cout << lis << endl;
}