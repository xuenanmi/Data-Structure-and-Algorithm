#include "ShortestPath.h"
#include<vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <queue>
#include <unordered_map>
#include "graph.h"
using namespace std;

Vertex ShortestPath::dijkstra(Graph g, Vertex a, Vertex b) {
  //initialize set of all vertices and arrays to keep track of distance and previous point
  std::vector<Vertex> set = g.getVertices();
  int size = set.size();
  vector<int> dist;
  dist.resize(size);
  vector<Vertex> prev;
  prev.resize(size); 
  //initialize prev and dist arrays
  for (size_t i = 0; i < set.size(); i++) {
      dist[i] = 1000000;
      if (set[i].compare(a) == 0) {
          dist[i] = 0;
      }
  }
  Vertex u = a;
  while (!set.empty()) {
    //print u to terminal 
    std::cout<<u<<std::endl;
    //get vertix with min dist from starting vertex
    int indexU = findIndex(set, u);
    int indexA = findIndex(set, a);
    int distU = dist[indexU];
    int min = 1000001;
    for (size_t i = 0; i < set.size(); i++){
      int current = dist[i];
      if ((i != indexU && i != indexA) && min > current - distU) {
         min = current - distU; 
         u = set[i];
      }
    }
    //take u out of the set
    set.erase (set.begin()+indexU);
    //if u is the target stop the search
    if (u.compare(b) == 0) {
      break;
    }
    //update arrays
    std::vector<Vertex> n= g.getAdjacent(u);
    for (size_t i = 0; i<n.size(); i++) {
      int distC = distU + g.getEdge(u, n[i]).weight_;
      int indexN = findIndex(set, n[i]);
      if (indexN > -1 && distC < dist[indexN]) {
        dist[indexN] = distC;
        prev[indexN] = u;
      }
    }
  }
  return u;
}

int ShortestPath::findIndex(std::vector<Vertex> v, Vertex a) {
    for(size_t i = 0; i < v.size(); i++) {
       if (v[i].compare(a) == 0) {
         return i;
       }
    }
    return -1;
}

//function for runing landmark algorithm, a as start, b as landmark and c as destination
void ShortestPath::landmark(Graph g, Vertex a, Vertex b, Vertex c) {
  vector<Vertex> result;
  vector<Vertex> path1 = dijkstra_(g, a, b);
  vector<Vertex> path2 = dijkstra_(g, b, c);
  //combine result of 
  result.insert(result.end(), path1.begin(), path1.end());
  result.insert(result.end(), path2.begin(), path2.end());
  std::ofstream myfile;
  myfile.open ("landmark_result.txt");
  //write content of result
  myfile << "Result of landmark is:\n";
  for (auto& it : result) {
    myfile << it;
    cout << it << endl;
    myfile << "\n";
  }
  myfile.close();
  cout << "Result has been saved to landmark_result.txt" << endl;
  return;
}

//helper method to get SSSP and return result as a vector
vector<Vertex> ShortestPath::dijkstra_(Graph g, Vertex start, Vertex end) {
  //unordered_map<string, string> predecessor;
	//unordered_map<string, int> distances;
  vector<Vertex> result;
  vector<Vertex> set = g.getVertices();
  int size = set.size();
  vector<int> dist;
  dist.resize(size, 1000000);
  vector<Vertex> prev; 
  prev.resize(size);
  //initialize prev and dist arrays
  for (size_t i = 0; i < set.size(); i++) {
      
      
      if (set[i].compare(start) == 0) {
          dist[i] = 0;
      }
  }
  Vertex u = start;
  while (!set.empty()) {
    //save the path
    result.push_back(u);
    //get vertix with min dist from starting vertex
    int indexU = findIndex(set, u);
    int indexA = findIndex(set, start);
    int distU = dist[indexU];
    int min = 1000001;
    for (size_t i = 0; i < set.size(); i++){
      int current = dist[i];
      if ((i != indexU && i != indexA) && min > current - distU) {
         min = current - distU; 
         u = set[i];
      }
    }
    //take u out of the set
    set.erase (set.begin()+indexU);
    //if u is the target stop the search
    if (u.compare(end) == 0) {
      break;
    }
    //update arrays
    std::vector<Vertex> n = g.getAdjacent(u);
    for (size_t i = 0; i<n.size(); i++) {
      int distC = distU + g.getEdge(u, n[i]).weight_;
      int indexN = findIndex(set, n[i]);
      if (indexN > -1 && distC < dist[indexN]) {
        dist[indexN] = distC;
        prev[indexN] = u;
      }
    }
  }
  return result;

}


