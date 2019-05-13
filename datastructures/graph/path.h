#ifndef PATH_H
#define PATH_H

#include "node.h"
#include <map>

class Path {
private:
	Node nodes_array[2];
	map <string, Node> nodes;
	double weight;
public:
	Path(Node first, Node second, double weight);

	Path(Node* nodes, double weight);

	Path(vector <Node> nodes, double weight);

	Node get_opposite(Node node);

	Node get_opposite(string name);

	bool in_path(Node node) {
		const string node_name = node.get("name");
		return (bool)this->nodes.count(node_name);
	};

	bool in_path(string name) {
		return (bool)this->nodes.count(name);
	};

	pair <Node, Node> get_nodes();

	double get_weight() {
		return this->weight;
	}
};

#endif