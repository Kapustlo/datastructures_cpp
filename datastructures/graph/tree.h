#pragma once

#ifndef TREE_H
#define TREE_H

#include "graph.h"

class Tree : public Graph {
private:
	vector <Node> children_to_remove;
	vector <string> names;
	map <int, vector <Node>> structure;
	int levels = 0;
public:
	Tree() {};
	Node add_node(string name, string value, int level = 1, vector <Node> parents = {});
	
	int get_height() {
		return levels;
	};

	map <int, vector <Node>> remove_node(Node node);
	map <int, vector <Node>> remove_node(string name);

	map <int, vector <Node>> get_structure() {
		return structure;
	};

	vector <Node> get_all_nodes_at_level(int level) {
		return structure[level];
	};

	vector <Node> get_all_nodes();

	string get_level_info(int level);
	string get_level_info(string level);
};

#endif