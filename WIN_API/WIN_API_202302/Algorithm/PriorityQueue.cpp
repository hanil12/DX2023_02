#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

template<typename T = int, typename Container = vector<int>, typename Pred = less<T>>
class Priority_Queue
{
public:
	// �θ� �ε��� n �� ��
	// �ڽ��� n * 2 + 1, n * 2 + 2 ��.

	void push(const T& value)
	{
		container.push_back(value);

		int nowIndex = static_cast<int>(container.size() - 1);

		while (true)
		{
			if (nowIndex <= 0)
			{
				return;
			}

			int parent = (nowIndex - 1) / 2;

			Pred p;
			if(!p(container[parent], container[nowIndex]))
				break;
			
			std::swap(container[parent], container[nowIndex]);
			nowIndex = parent;
		}
	}

	void pop() 
	{
		if(container.empty())
			return;

		std::swap(container[0], container.back());
		container.pop_back();

		int nowIndex = 0;

		while (true)
		{
			int leftChild = nowIndex * 2 + 1;
			int rightChild = nowIndex * 2 + 2;

			// Child ��ü�� ����.
			if(leftChild >= (int)container.size())
				break;

			int nextIndex = nowIndex;
			Pred p;
			if(p(container[nextIndex], container[leftChild]))
				nextIndex = leftChild;

			if(rightChild < (int)container.size() && p(container[nextIndex],container[rightChild]))
				nextIndex = rightChild;

			if(nextIndex == nowIndex)
				break;

			std::swap(container[nowIndex], container[nextIndex]);
			nowIndex = nextIndex;
		}
	}

	const T& top() { return container[0]; }

	unsigned int size() { return container.size(); }

	bool empty() { return container.empty(); }

private:
	Container container;
};

int main()
{
	// priority_queue�� ��������Ʈ���� �����Ǿ��ִ�.
	// ��������Ʈ���� �迭�� �̿��ؼ� ������ �� �ִ�.

	// ���̷�
	// 
	Priority_Queue<int, vector<int>, greater<int>> pq;
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