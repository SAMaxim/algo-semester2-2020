#include <iostream>
#include <vector>
#include<algorithm>

using namespace std;

enum color
{
	white,
	gray,
	black
};

typedef vector<vector<int>> my_graph;

bool DFS_Find_Cycle(const my_graph& g, vector<color>& colors, int v)
{
	colors[v] = gray;
	for (int u : g[v])
	{
		if (colors[u] == white)
		{
			if (DFS_Find_Cycle(g, colors, u))
				return true;
		}
		else if (colors[u] == gray)
			return true;
	}
	colors[v] = black;
	return false;
}

void Topological_Sort(const my_graph& g, vector<int>& answer, vector<color>& colors, int v)
{
	colors[v] = gray;
	for (int u : g[v])
	{
		if (colors[u] == white)
			Topological_Sort(g, answer, colors, u);

	}
	colors[v] = black;
	answer.push_back(v);
}

int main()
{
	int nv, ne;
	cin >> nv >> ne;
	my_graph g(nv);
	for (int i = 0; i < ne; ++i)
	{
		int v0, v1;
		cin >> v0 >> v1;
		g[v0].push_back(v1);
	}
	vector <color> colors(nv);
	for (int i = 0; i < nv; ++i)
	{
		if (colors[i] == white && DFS_Find_Cycle(g, colors, i))
		{
			cout << "NO";
			return 0;
		}
	}
	fill(colors.begin(), colors.end(), white);
	vector <int> answer;
	for (int i = 0; i < nv; ++i)
	{
		if (colors[i] == white)
			Topological_Sort(g, answer, colors, i);
	}
	reverse(answer.begin(), answer.end());
	cout << "YES" << endl;
	for (int i = 0; i < answer.size(); ++i)
		cout << answer[i] << " ";
	return 0;

}
