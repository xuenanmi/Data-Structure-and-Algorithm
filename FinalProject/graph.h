#pragma once
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include "edge.h"


using std::vector;
using std::unordered_map;

class Graph
{
public:
	/**
	 * Constructor to create an empty graph.
	 */
	Graph();

	/**
	 * Constructor to create a graph from the reading file
	 * @param filename - the file name of input data set
	 */
	Graph(std::string filename);


	/**
	 * Gets all adjacent vertices to the parameter vertex.
	 * @param source - vertex to get neighbors from
	 * @return a vector of vertisces
	 */
	vector<Vertex> getAdjacent(Vertex source) const;


	/**
	 * Gets all vertices in the graph.
	 * @return a vector of all vertices in the graph
	 */
	vector<Vertex> getVertices() const;


	/**
	 * Gets all the edges in the graph.
	 * @return a vector of all the edges in the graph
	 */
	vector<Edge> getEdges() const;

	/**
	 * Gets an edge between two vertices.
	 * @param source - one vertex the edge is connected to
	 * @param destination - the other vertex the edge is connected to
	 * @return - if exist, return the corresponding edge
	 *         - if edge doesn't exist, return Edge()
	 */
	Edge getEdge(Vertex source, Vertex destination) const;


private:
	mutable unordered_map<Vertex, unordered_map<Vertex, Edge>> adjacency_list;
};

