#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

// DP : Dynamic Programming(동적 계획법)
// 컴퓨터 공학의 Dynamic과는 아무련 관련이 없다.
// => 멋있어서
// ==> 수학에서 최적화 기법으로 나온 알고리즘 디자인 패러다임.

// 캐싱:
int chache[100];

// 부분 문제: 
// f(n) = f(n-1) + f(n-2)

// 참조 무결성: 

// 피보나치 수열
// f(0) = 1
// f(1) = 1
// f(n) = f(n-1) + f(n-2)
// f(2) = 2
// f(3) = 3



int Fibonacci(int n, int& count)
{
	// 기저사항
	if(n == 0 || n == 1)
		return 1;

	if (n == 2)
		++count;

	// 메모이제이션, 캐싱
	if(chache[n] != -1)
		return chache[n];

	// 구하기
	chache[n] = Fibonacci(n - 1, count) + Fibonacci(n - 2, count);

	return chache[n];
}

int main()
{
	int count = 0;

	for (int i = 0; i < 100; i++)
	{
		chache[i] = -1;
	}

	__int64 start = GetTickCount64();

	cout << Fibonacci(99, count) << endl;
	cout << count << endl;

	__int64 end = GetTickCount64();

	cout << end - start << "ms" << endl;

	return 0;
}