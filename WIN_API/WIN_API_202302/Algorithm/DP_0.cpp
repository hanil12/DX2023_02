#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

// DP : Dynamic Programming(���� ��ȹ��)
// ��ǻ�� ������ Dynamic���� �ƹ��� ������ ����.
// => ���־
// ==> ���п��� ����ȭ ������� ���� �˰��� ������ �з�����.

// ĳ��:
int chache[100];

// �κ� ����: 
// f(n) = f(n-1) + f(n-2)

// ���� ���Ἲ: 

// �Ǻ���ġ ����
// f(0) = 1
// f(1) = 1
// f(n) = f(n-1) + f(n-2)
// f(2) = 2
// f(3) = 3



int Fibonacci(int n, int& count)
{
	// ��������
	if(n == 0 || n == 1)
		return 1;

	if (n == 2)
		++count;

	// �޸������̼�, ĳ��
	if(chache[n] != -1)
		return chache[n];

	// ���ϱ�
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