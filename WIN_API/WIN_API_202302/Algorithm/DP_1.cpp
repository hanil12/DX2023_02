#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

// ENCHANT

// ��ȭ�� �ϴµ�
// + 1
// + 2
// + 3

// 0�� f(0)
// 1

// 1�� f(1)
// 1

// 2�� f(2)
// 2

// 3�� f(3) = 4
// 1 1 1
// 1 2
// 2 1
// 3

// 4�� f(4) = 
// 1 1 1 1
// 1 2 1
// 2 2
// 3 1
// 1 3
// 2 1 1
// 1 1 2

// N���� �ϰ� �ʹ�... �� �� ��ȭ�ϴ� ��� ������ ��� ����� ��
// 3���� �ϰ� �ʹ�...
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
//	// ĳ��
//	int& ref = cache[N];
//	if(ref != -1)
//		return ref;
//
//	// ���ϱ�
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