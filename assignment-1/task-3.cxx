#include <iostream>
#include <vector>
#include <algorithm>

enum color
{
	white,
	gray,
	black
};


using namespace std;

typedef vector <vector <int>> graph;


void Close_Time(const graph& g, vector <color>& colors, vector<int>& ft, int& t, int v)
{
	colors[v] = gray;
	++t;
	for (int u : g[v])
	{
		if (colors[u] == white)
			Close_Time(g, colors, ft, t, u);
	}
	ft[v] = t++;
	colors[v] = black;
}

void Set_Comp(const graph& g, vector<color>& colors, vector <int>& comp, int c, int v)
{
	colors[v] = gray;
	comp[v] = c;
	for (int u : g[v])
	{
		if (colors[u] == white)
			Set_Comp(g, colors, comp, c, u);
	}
	colors[v] = black;
}


int main()
{
	int nv, ne;
	cin >> nv >> ne;
	graph g(nv);
	graph g_invert(nv);
	for (int i = 0; i < ne; ++i)
	{
		int v, u;
		cin >> v >> u;
		int vnorm = v - 1, unorm = u - 1;
		g[vnorm].push_back(unorm);
		g_invert[unorm].push_back(vnorm);
	}
	vector <color> colors(nv);
	vector <int> ft(nv);
	int t = 0;
	for (int i = 0; i < nv; ++i)
	{
		if (colors[i] == white)
			Close_Time(g_invert, colors, ft, t, i);
	}

	vector <int> o(nv);
	for (int i = 0; i < nv; ++i)
		o[i] = i;
	sort(o.begin(), o.end(), [&ft](int v, int u) {return ft[v] > ft[u]; });

	fill(colors.begin(), colors.end(), white);
	vector<int> comp(nv);
	int c = 0;
	for (int i = 0; i < nv; ++i)
	{
		int v = o[i];
		if (colors[v] == white)
			Set_Comp(g, colors, comp, c++, v);
	}
	if (c == 1)
	{
		cout << 0;
		return 0;
	}
	graph dag(c);
	for (int i = 0; i < g.size(); ++i)
	{
		for (int u : g[i])
		{
			if (comp[i] != comp[u])
				dag[comp[i]].push_back(comp[u]);
		}
	}

	vector <int> in(c, 0);
	vector <int> out(c, 0);
	int k_in = 0, k_out = 0;
	for (int i = 0; i < dag.size(); ++i)
	{
		for (int u : dag[i])
		{
			out[i] ++;
			in[u] ++;
		}
	}
	for (int i = 0; i < c; ++i)
	{
		if (in[i] == 0)
			k_in++;
		if (out[i] == 0)
			k_out++;
	}
	cout << max(k_in, k_out);
	return 0;

}
