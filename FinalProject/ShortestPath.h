#pragma once
#include "graph.h"
#include <vector>
using namespace std;

class ShortestPath {
 public:
 /*method to run Dijkstra's algorithm and output results to a .txt file
 @param Graph g: directed graph to run the algorithm on
 @param Vertex a: starting vertex for path
 @param Vertex b: ebding vertex of path
 */
 Vertex dijkstra(Graph g, Vertex a, Vertex b);
 /* method to find index of specific vertex vithin the parameter vector
 @param std::vector<Vertex> v: vector of vertexs to search
 @param Vertex a: vertex to find the index of
 */
 int findIndex(std::vector<Vertex> v, Vertex a);
 /*method to run Landmark path algorithm and output results to a .txt file
 @param Graph g: directed graph to run the algorithm on
 @param Vertex a: starting vertex for path
 @param Vertex b: ending vertex of path
 @param Vertex c: vertex path must go through
 */
 void landmark(Graph g, Vertex a, Vertex b, Vertex c);

 vector<Vertex> dijkstra_(Graph g, Vertex start, Vertex end);   
};
