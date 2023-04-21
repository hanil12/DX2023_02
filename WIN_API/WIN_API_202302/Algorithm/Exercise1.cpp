#include <string>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

vector<bool> visited;
vector<string> result;

void DFS(int here, const vector<vector<string>>& tickets)
{
    if (std::all_of(visited.begin(), visited.end(), [](const bool& value)-> bool { return value == true; }))
        return;

    visited[here] = true;
    string thereString = tickets[here][1];
    result.push_back(thereString);

    for (int i = 0; i < tickets.size(); i++)
    {
        if(visited[i] == true)
            continue;

        if (thereString == tickets[i][0])
        {
            DFS(i, tickets);
        }
    }
}

vector<string> solution(vector<vector<string>> tickets) {

    visited.resize(tickets.size(), false);

    std::sort(tickets.begin(), tickets.end(), [](const vector<string>& a, const vector<string>& b)-> bool
        {
            if (a[0] == b[0])
            {
                if (a[1] < b[1])
                    return true;
            }
            return false;
        });

    result.push_back("ICN");
    DFS(0, tickets);

    return result;
}


int main()
{
    vector<vector<string>> temp;

    temp.push_back({ "ICN", "SFO" });
    temp.push_back({ "ICN", "ATL" });
    temp.push_back({ "SFO", "ATL" });
    temp.push_back({ "ATL", "ICN" });
    temp.push_back({ "ATL", "SFO" });
    solution(temp);

    return 0;
}