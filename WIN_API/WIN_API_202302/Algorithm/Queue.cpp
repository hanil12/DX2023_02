#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

template <typename T, typename Container = deque<T>>
class MyQueue
{
public:
	void push(const T& value)
	{
		c.push_back(value);
	}

	void pop()
	{
		c.pop_front();
	}

	const T& front()
	{
		return c.front();
	}

	bool empty()
	{
		return c.size() == 0;
	}

private:
	Container c;
};

int main()
{
	MyQueue<int> q;
	q.push(5);
	q.push(8);
	q.push(3);
	q.push(1);
	q.push(9);

	while (true)
	{
		if(q.empty() == true)
			break;

		int value = q.front();
		cout << value << endl;
		q.pop();
	}

	return 0;
}