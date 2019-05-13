#pragma once

#ifndef GRAPH_H
#define GRAPH_H

#include "path.h"

class Graph {
private:
	map <string, Node> nodes;
	vector <Path> paths;

	map <int, Path> get_node_paths(Node node);

	map <int, Path> get_node_paths(string name);

	map <string, double> mod_table(map <string, double> table, Node current, Node to, vector <string> visited = {});

public:
	Graph() {};

	Node get_node(string name) {
		return this->nodes.find(name)->second;
	};

	Node add_node(string name, string value = "");

	Path connect_nodes(string first, string second, double weight);

	Path connect_nodes(Node first, Node second, double weight);

	vector <Path> remove_node(Node node);

	vector <Path> remove_node(string name);

	string get_paths();

	double get_distance(Node node_from, Node node_to);

	double get_distance(string from_name, string to_name);
};

#endif