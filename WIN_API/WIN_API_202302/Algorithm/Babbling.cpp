#include <string>
#include <vector>

using namespace std;

vector<bool> visited;
string arr[4] = { "aya", "ye", "woo", "ma" };
vector<string> allBabbling;

void DFS(int start, string word)
{
	if (word.size() >= 10)
		return;

	string makeWord = word + arr[start];
	allBabbling.push_back(makeWord);
	visited[start] = true;

	for (int i = 0; i < 4; i++)
	{
		if (start == i)
			continue;
		if (visited[i] == true)
			continue;
		DFS(i, makeWord);
	}

	visited[start] = false;
}

int solution(vector<string> babbling) {
	int answer = 0;

	visited = vector<bool>(4, false);

	for (int i = 0; i < 4; i++)
	{
		DFS(i, "");
	}

	for (auto string : allBabbling)
	{
		for (auto str : babbling)
		{
			if (string == str)
				answer++;
		}
	}

	return answer;
}

int main()
{
	return 0;
}