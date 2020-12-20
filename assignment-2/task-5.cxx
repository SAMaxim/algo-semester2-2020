#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

typedef std::vector<std::vector<int>>    Graph;
typedef std::vector<std::vector<double>> WGraph;

struct Vertex
{
	Vertex(double weight, int vertex)
		:w(weight), v(vertex)
	{}

	double w;
	int v;
};

bool operator< (const Vertex& v1, const Vertex& v2)
{
	return v1.w < v2.w;
}

double dijkstra(Graph g, WGraph wt, int v0, int v1)
{
	std::vector<int> parents(g.size(), -1);
	std::vector<double> d(g.size(), std::numeric_limits<double>::min());
	std::priority_queue <Vertex> q;

	d[v0] = 1;
	q.push(Vertex(d[v0], v0));

	while (!q.empty())
	{
		int v = q.top().v;
		q.pop();

		if (v == v1)
			return d[v1];

		for (int iu = 0; iu < g[v].size(); ++iu)
		{
			int u = g[v][iu];
			double w = wt[v][iu];
			if (d[v] * w > d[u])
			{
				d[u] = d[v] * w;
				parents[u] = v;
				q.push(Vertex(d[u], u));
			}
		}
	}
}

int main()
{
	int nv, ne, v0, v1;
	std::cin >> nv >> ne >> v0 >> v1;
	Graph  g(nv);
	WGraph wt(nv);

	--v0;
	--v1;

	for (int i = 0; i < ne; ++i)
	{
		int v, u;
		double w;
		std::cin >> v >> u >> w;
		--v;
		--u;
		double nw = 1 - w / 100;
		g[v].push_back(u);
		g[u].push_back(v);
		wt[v].push_back(nw);
		wt[u].push_back(nw);
	}

	std::cout << (1 - dijkstra(g, wt, v0, v1));
	return 0;
}
