#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

class Priority_Queue
{
public:
	// �θ� �ε��� n �� ��
	// �ڽ��� n * 2 + 1, n * 2 + 2 ��.

	void push(const int& value) {}

	void pop() {}

	const int& top() { return 0; }

	unsigned int size() { return 0; }

	bool empty() { return false; }

private:
	vector<int> container;
};

int main()
{
	// priority_queue�� ��������Ʈ���� �����Ǿ��ִ�.
	// ��������Ʈ���� �迭�� �̿��ؼ� ������ �� �ִ�.

	// ���̷�
	// 

	priority_queue<int> pq;
	pq.push(10);
	pq.push(7);
	pq.push(20);
	pq.push(11);
	pq.push(4);

	cout << pq.top() << endl;
	pq.pop();

	cout << pq.top() << endl;
	pq.pop();

	cout << pq.top() << endl;
	pq.pop();

	return 0;
}