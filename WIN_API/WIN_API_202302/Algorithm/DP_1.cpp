#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

// ENCHANT

// 강화를 하는데
// + 1
// + 2
// + 3

// 0강 f(0)
// 1

// 1강 f(1)
// 1

// 2강 f(2)
// 2

// 3강 f(3) = 4
// 1 1 1
// 1 2
// 2 1
// 3

// 4강 f(4) = 
// 1 1 1 1
// 1 2 1
// 2 2
// 3 1
// 1 3
// 2 1 1
// 1 1 2

// N강을 하고 싶다... 이 때 강화하는 대로 나오는 모든 경우의 수
// 3강을 하고 싶다...
// 1 1 1
// 1 2
// 2 1
// 3


vector<int> cache = vector<int>(100, -1);
int Num = 10;
//int Enchant(int N)
//{
//	if(N > Num)
//		return 0;
//
//	if(N == Num)
//		return 1;
//
//	// 캐쉬
//	int& ref = cache[N];
//	if(ref != -1)
//		return ref;
//
//	// 구하기
//	ref = Enchant(N + 1) + Enchant(N + 2) + Enchant(N + 3);
//
//	return ref;
//}

int Enchant(int N)
{
    if (N == 0 || N == 1)
        return 1;
    if (N == 2)
        return 2;

    if (cache[N] != -1)
        return cache[N];

    cache[N] = Enchant(N - 1) + Enchant(N - 2) + Enchant(N - 3);

    return cache[N];
}

int main()
{
	cout << Enchant(10) << endl;
}