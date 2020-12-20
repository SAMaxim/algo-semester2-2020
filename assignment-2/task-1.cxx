#include <iostream>
#include <vector>
#include <limits>
#include <queue>

using std::vector;


struct Vertex
{
	size_t v;
	size_t w;

	bool operator>(const Vertex& V) const
	{
		return this->w > V.w;
	}
};


size_t dijkstra(size_t from, size_t to, size_t f_type, size_t s_type, size_t vertex_num)
{
	constexpr size_t inf = std::numeric_limits<int>::max();
	std::priority_queue<Vertex, vector<Vertex>, std::greater<Vertex>> heap;
	std::vector<size_t> dist(vertex_num, inf);
	heap.push({ from, 0 });
	while (!heap.empty() && dist[to] == inf)
	{
		Vertex u = heap.top();
		size_t v = (u.v + 1) % vertex_num;
		size_t w = f_type;
		if (dist[v] == inf)
			heap.push({ v, w + u.w });
		v = (u.v * u.v + 1) % vertex_num;
		w = s_type;
		if (dist[v] == inf)
			heap.push({ v, w + u.w });
		if (dist[heap.top().v] == inf)
			dist[heap.top().v] = heap.top().w;
		while (!heap.empty() && dist[heap.top().v] != inf)
			heap.pop();
	}
	return dist[to];
}

int main()
{
	size_t f_type;
	size_t s_type;
	size_t vertex_num;
	size_t from, to;
	std::cin >> f_type >> s_type >> vertex_num >> from >> to;
	std::cout << dijkstra(from, to, f_type, s_type, vertex_num);
}
