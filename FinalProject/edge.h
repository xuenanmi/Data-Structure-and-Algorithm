#pragma once
#include <string>

typedef std::string Vertex;

class Edge
{
public:
	/**
	* Constructor to create an empty edge.
	*/
	Edge() : source(Vertex()), dest(Vertex()), weight_(double()), label_(std::string()) {};

	/**
	* Constructor to create a graph from the reading file
	* @param u - the source airport
	* @param v - the destination airport
	*/
	Edge(Vertex u, Vertex v) 
		: source(u), dest(v),weight_(0), label_("unexplored") {};

	/**
	*Set the weight of edge
	*@param weight - number of routes that connect to the source airport
	*/
	void setWeight(double weight)
	{
		weight_ = 1/weight;
		return;
	}
	
	/**
	* Compares two edges' source and dest.
	* @param other - the edge to compare with
	*/
	bool operator==(Edge& other) const
	{
		if (this->source != other.source)
			return false;
		if (this->dest != other.dest)
			return false;
		return true;
	}

	Vertex dest;
	Vertex source;
	double weight_;
	std::string label_;
};

