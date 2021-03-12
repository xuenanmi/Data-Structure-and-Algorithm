#include "graph.h"
#include "DFS.h"
#include "ShortestPath.h"
#include <vector>
#include <iostream>
int main (int argx, char *argv[]) {
	Graph g("routes.dat");
	std::vector<Vertex> v = g.getVertices();
	std::cout<<"DFS traversal"<<std::endl;
	DFS d(g);
	ShortestPath s;
	std::cout<<" "<<std::endl;
	std::cout<<"Dijkstra's algorithm"<<std::endl;
	s.dijkstra(g, v[0], v[3]);
	s.landmark(g, v[0], v[3], v[1]); 
	return 0;
}
