#include "../catch/catch.cpp"
#include "../graph.h"
#include "../edge.h"
#include "../DFS.h"
#include "../ShortestPath.h"
#include <vector>

TEST_CASE("dijkstra method returns a result") {
	Graph g("routes.dat");
	std::vector<Vertex> v  = g.getVertices();
	ShortestPath s;
	REQUIRE(s.dijkstra(g, v[0], v[5]) != v[0]);
}

TEST_CASE("dijkstra method ends on target vertex"){
	Graph g("routes.dat");
	std::vector<Vertex> v  = g.getVertices();
	ShortestPath s;
	REQUIRE(s.dijkstra(g, v[0], v[5]) == v[5]);
}

TEST_CASE("findIndex method works correctly"){
	std::vector<Vertex> v;
	v.push_back("1");
	v.push_back("2");
	v.push_back("3");
	ShortestPath s;
	REQUIRE(s.findIndex(v, "2") == 1);
}
