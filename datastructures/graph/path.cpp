#include "path.h"

Path::Path(Node first, Node second, double weight) {
	const string name_first = first.get("name");
	const string name_second = second.get("name");

	this->nodes.emplace(make_pair(name_first, first));
	this->nodes.emplace(make_pair(name_second, second));

	this->nodes_array[0] = first;
	this->nodes_array[1] = second;

	this->weight = weight;
};

Path::Path(Node* nodes, double weight) {
	for (int i = 0; i < 2; i++) {
		Node node = nodes[i];
		const string node_name = node.get("name");
		this->nodes.emplace(make_pair(node_name, node));
		this->nodes_array[i] = node;
	}

	this->weight = weight;
};

Path::Path(vector <Node> nodes, double weight) {
	const int nodes_size = nodes.size();
	if (nodes_size == 2) {
		for (size_t i = 0; i < nodes_size; i++) {
			Node node = nodes[i];
			const string node_name = node.get("name");
			this->nodes.emplace(make_pair(node_name, node));
			this->nodes_array[i] = node;
		}

		this->weight = weight;
	}
	else {
		throw("Error, incorrect vector size. Required: 2");
	}
};

Node Path::get_opposite(Node node) {
	const string node_name = node.get("name");

	Node first_node = this->nodes_array[0];
	Node second_node = this->nodes_array[1];

	const string first_name = first_node.get("name");
	const string second_name = second_node.get("name");

	if (first_name == node_name)
		return second_node;
	else if (second_name == node_name)
		return first_node;
	else 
		throw("Error, node not found in the path");
};

Node Path::get_opposite(string name) {
	Node first_node = this->nodes_array[0];
	Node second_node = this->nodes_array[1];

	const string first_name = first_node.get("name");
	const string second_name = second_node.get("name");

	if (first_name == name)
		return second_node;
	else if (second_name == name)
		return first_node;
	else
		throw("Error, node not found in the path");
};

pair <Node, Node> Path::get_nodes() {
	vector <Node> nodes;
	map <string, Node>::iterator it = this->nodes.begin();
	for (; it != this->nodes.end(); it++) {
		nodes.push_back(it->second);
	} 

	return make_pair(nodes[0], nodes[1]);
}