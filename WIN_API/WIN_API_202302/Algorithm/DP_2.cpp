#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

// LIS (Longest Increasing Sequence)
// 부분 증가 수열에서 제일 긴 수열 길이를 찾는다.
// Seq : 1 2 9 5 8 10

// 부분 수열 : 순서는 유지하되, 인접하지 않을 수도 있다.
// 1 2 5 (O)
// 1 2 9 8 (O)
// 2 9 1 (X)

// 부분 증가 수열 : 부분 수열이면서 점점 증가되는 순서로 유지되는 수열
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