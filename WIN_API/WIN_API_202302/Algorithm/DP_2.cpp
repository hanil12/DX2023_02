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

vector<int> seq = {0,5,1,2,3,1};

// LIS(5) : 1
// LIS(4) : LIS(5) or LIS(5) + 1
// LIS(3) : LIS(4) or LIS(4) + 1
// LIS(2) : LIS(3) or LIS(3) + 1
// LIS(1) : LIS(2) or LIS(2) + 1
// LIS(0) : LIS(1) or LIS(1) + 1 => 4

int LIS(int pos)
{
	return 0;
}

int main()
{
	cout << LIS(0) << endl;
}