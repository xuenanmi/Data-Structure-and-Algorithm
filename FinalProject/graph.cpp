#include "graph.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <set>
using std::vector;




Graph::Graph()
{
}


Graph::Graph(std::string filename)
{
	std::string read;
	std::string temp;
	std::ifstream text;
	std::ofstream out;
	Vertex source;
	Vertex dest;
	vector <std::string> record;
	double siz;
	text.open(filename);
	out.open("out.txt");
	if (text.is_open())
	{
		while (std::getline(text, read))
		{

			std::istringstream ss(read);
			
			while (ss)
			{
				std::getline(ss, temp, ',');
				record.push_back(temp);
			}
			source = record[3];
			dest = record[5];
			out << source << ", " << dest << std::endl;
			adjacency_list[source][dest] = Edge(source, dest);
			record.clear();
		}

	}
	for (auto i = adjacency_list.begin(); i != adjacency_list.end(); ++i)
	{
		siz = double(i->second.size());
		
		for (auto j = i->second.begin(); j != i->second.end(); j++)
		{
			j->second.setWeight(siz);
		}
	}
	text.close();
	out.close();

};

vector<Vertex> Graph::getAdjacent(Vertex source) const
{
	auto lookup = adjacency_list.find(source);

	if (lookup == adjacency_list.end())
		return vector<Vertex>();

	else
	{
		vector<Vertex> vertex_list;
		std::unordered_map <Vertex, Edge>& map = adjacency_list[source];
		for (auto it = map.begin(); it != map.end(); it++)
		{
			vertex_list.push_back(it->first);
		}
		return vertex_list;
	}
}
vector<Vertex> Graph::getVertices() const
{
	vector<Vertex> ret;

	for (auto it = adjacency_list.begin(); it != adjacency_list.end(); it++)
	{
		ret.push_back(it->first);
	}

	return ret;
}

vector<Edge> Graph::getEdges() const
{
	if (adjacency_list.empty())
		return vector<Edge>();

	vector<Edge> ret;
	std::set<std::pair<Vertex, Vertex>> seen;

	for (auto it = adjacency_list.begin(); it != adjacency_list.end(); it++)
	{
		Vertex source = it->first;
		for (auto its = adjacency_list[source].begin(); its != adjacency_list[source].end(); its++)
		{
			Vertex destination = its->first;
			if (seen.find(make_pair(source, destination)) == seen.end())
			{
				//this pair is never added to seen
				ret.push_back(its->second);
				seen.insert(make_pair(source, destination));
			}
		}
	}

	return ret;
}

Edge Graph::getEdge(Vertex source, Vertex destination) const
{
	if (adjacency_list.find(source) == adjacency_list.end())
		return Edge();
	if (adjacency_list[source].find(destination) == adjacency_list[source].end())
		return Edge();
	Edge ret = adjacency_list[source][destination];
	return ret;
}