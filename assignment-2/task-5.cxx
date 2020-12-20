#include <iostream>
#include <vector>

using std::vector;

int main()
{
	int N, M, S;
	float V;
	std::cin >> N >> M >> S >> V;
	--S;

	vector<vector<int>>   G(N);
	vector<vector<float>> C(N);
	vector<vector<float>> R(N);

	for (int i = 0; i < M; ++i)
	{
		int u, v;
		float Rvu, Cvu, Ruv, Cuv;
		std::cin >> v >> u >> Rvu >> Cvu >> Ruv >> Cuv;
		--v;
		--u;
		G[v].push_back(u);
		G[u].push_back(v);
		R[v].push_back(Rvu);
		R[u].push_back(Ruv);
		C[v].push_back(Cvu);
		C[u].push_back(Cuv);
	}

	vector<float> V0(N, 0);
	V0[S] = V;

	for (int i = 0; i < N - 1; ++i)
		for (int v = 0; v < G.size(); ++v)
			for (int iu = 0; iu < G[v].size(); ++iu)
			{
				int u = G[v][iu];
				float Rvu = R[v][iu];
				float Cvu = C[v][iu];
				float Vu = (V0[v] - Cvu) * Rvu;
				if (Vu > V0[u])
					V0[u] = Vu;
			}

	for (int v = 0; v < G.size(); ++v)
		for (int iu = 0; iu < G[v].size(); ++iu)
		{
			int u = G[v][iu];
			float Rvu = R[v][iu];
			float Cvu = C[v][iu];
			float Vu = (V0[v] - Cvu) * Rvu;
			if (Vu > V0[u])
			{
				std::cout << "YES";
				return 0;

			}
		}

	std::cout << "NO";
	return 0;
}
