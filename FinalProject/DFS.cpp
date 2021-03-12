#include "DFS.h"
#include <stack>
#include <iostream>
#include <list>
using std::cout;


DFS::DFS(Graph g){

  vector<Vertex> vertices = g.getVertices();
  int num_vertices = vertices.size() ; // number of vertices in the Graph
  bool *visited = new bool[num_vertices];
  for (int i = 0; i < num_vertices; i++){
    visited[i] = false; //label all vertex as non-visited
  }

  for (int i = 0; i < num_vertices; i++){
     if (visited[i] == false) {
        DFS_helper(g, i, visited);
     }
  }

}

void DFS::DFS_helper(Graph g, int v, bool visited[]){
   visited[v] = true; //label current vertex as visited
   vector<Vertex> vertices = g.getVertices();
  
   //recurse for each vertex adjacent to this vertex v 
   Vertex curr_v = vertices[v];
   std::cout << curr_v << " ";
   vector<Vertex>  w =  g.getAdjacent(curr_v);
   for (auto i : w){
     int index = getIdxVertex(g, i);
     if (!visited[index]) {
        DFS_helper(g, index, visited);
     }
   }
}

int DFS::getIdxVertex(Graph g, Vertex v){
   vector<Vertex> vertices = g.getVertices();
   auto it = find(vertices.begin(), vertices.end(), v);
   int index = it - vertices.begin();
   return index;
}




