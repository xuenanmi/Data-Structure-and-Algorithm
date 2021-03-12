#pragma once
#include "graph.h"
#include "edge.h"

class DFS{

  public:
     DFS(Graph g);
     void DFS_helper (Graph g, int v, bool visited[]);
     int getIdxVertex(Graph g, Vertex v);
     //void DFS_helper (int v, bool visited[]);
     Graph gr;
};
