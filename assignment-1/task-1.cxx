#include <iostream>
#include <vector>
#include <queue>

using namespace std;

enum color
{
	white,
	gray,
	black
};

void BFS(int v, vector <vector <int >>& g, vector <color>& colors, vector<int>& distance)
{
	queue <int> q;
	q.push(v);
	colors[v] = gray;
	while (!q.empty())
	{
		int f = q.front();
		q.pop();
		colors[f] = black;
		for (int u : g[f])
		{
			if (colors[u] == white)
			{
				distance[u] = distance[f] + 1;
				q.push(u);
				colors[u] = gray;

			}
		}
	}

}

int main()
{
	int nv, ne, v1, v2, v3;
	cin >> nv >> ne >> v1 >> v2 >> v3;
	int v1norm = v1 - 1, v2norm = v2 - 1, v3norm = v3 - 1;
	vector <vector <int>> g(nv);
	vector <color> colors(nv);
	vector <int> distance(nv);
	for (int i = 0; i < ne; ++i)
	{
		int v, u;
		cin >> v >> u;
		int vnorm = v - 1, unorm = u - 1;
		g[vnorm].push_back(unorm);
		g[unorm].push_back(vnorm);

	}
	vector <int> leon(nv, 0);
	vector <int> mat(nv, 0);
	vector <int> milk(nv, 0);
	BFS(v1norm, g, colors, leon);
	fill(colors.begin(), colors.end(), white);
	BFS(v2norm, g, colors, mat);
	fill(colors.begin(), colors.end(), white);
	BFS(v3norm, g, colors, milk);
	int min = 200000;
	for (int i = 0; i < nv; ++i)
	{
		int sum = leon[i] + mat[i] + milk[i];
		if (sum < min)
			min = sum;
	}
	cout << min;
	return 0;

}
