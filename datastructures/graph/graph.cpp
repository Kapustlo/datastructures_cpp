#include "graph.h"

// PUBLIC METHODS

Node Graph::add_node(string name, string value) {
	Node node(name, value);
	auto result = this->nodes.emplace(name, node);
	if (result.second)
		return node;
	else
		throw("Error, node name is not unique");
};

Path Graph::connect_nodes(string first, string second, double weight) {
	Node first_node = this->get_node(first);
	Node second_node = this->get_node(second);
	Path path(first_node, second_node, weight);
	this->paths.push_back(path);
	return path;
};

Path Graph::connect_nodes(Node first, Node second, double weight) {
	Path path(first, second, weight);
	this->paths.push_back(path);
	return path;
};

vector <Path> Graph::remove_node(Node node) {
	const size_t paths_size = this->paths.size();
	const string node_name = node.get("name");
	const int node_exists = this->nodes.count(node_name);
	if (paths_size && node_exists) {
		map <int, Path> node_paths = this->get_node_paths(node);
		map <int, Path>::iterator it = node_paths.begin();
		for (; it != node_paths.end(); it++)
			this->paths.erase(this->paths.begin() + it->first);
		return this->paths;
	}
};

vector <Path> Graph::remove_node(string name) {
	const int paths_size = this->paths.size();
	const int node_exists = this->nodes.count(name);
	if (paths_size && node_exists) {
		map <int, Path> node_paths = this->get_node_paths(name);
		map <int, Path>::iterator it = node_paths.begin();
		for (; it != node_paths.end(); it++)
			this->paths.erase(this->paths.begin() + it->first);
		return this->paths;
	}
};

string Graph::get_paths() {
	string result = "";
	for (size_t i = 0; i < this->paths.size(); i++) {

		Path path = this->paths[i];
		pair <Node, Node> nodes = path.get_nodes();
		Node first = nodes.first;
		Node second = nodes.second;
		const string first_name = first.get("name");
		const string second_name = first.get("name");
		const string weight = to_string(path.get_weight());
		result += first_name + " <---> " + second_name + " " + weight + "\n";

	}
	return result;
};

double Graph::get_distance(Node node_from, Node node_to) {
	map <string, double> table;
	map <string, Node>::iterator it = this->nodes.begin();
	const string to_name = node_to.get("name");
	for (; it != this->nodes.end(); it++) {
		const string key = it->first;
		double value;
		if (key == node_from.get("name"))
			value = 0.0;
		else
			value = DBL_MAX;
		table.emplace(make_pair(key, value));
	}
	return this->mod_table(table, node_from, node_to)[to_name];
};

double Graph::get_distance(string from_name, string to_name) {
	Node node_from = this->get_node(from_name);
	Node node_to = this->get_node(to_name);
	map <string, double> table;
	map <string, Node>::iterator it = this->nodes.begin();

	for (; it != this->nodes.end(); it++) {
		const string key = it->first;
		double value;
		if (key == node_from.get("name"))
			value = 0.0;
		else
			value = DBL_MAX;
		table.emplace(make_pair(key, value));
	}
	return this->mod_table(table, node_from, node_to)[to_name];
};

// PRIVATE METHODS

map <int, Path> Graph::get_node_paths(Node node) {
	map <int, Path> result;
	for (size_t i = 0; i < this->paths.size(); i++) {
		Path path = this->paths[i];
		if (path.in_path(node))
			result.emplace(make_pair(i, path));
	}
	return result;
};

map <int, Path> Graph::get_node_paths(string name) {
	map <int, Path> result;
	for (size_t i = 0; i < this->paths.size(); i++) {
		Path path = this->paths[i];
		if (path.in_path(name))
			result.emplace(make_pair(i, path));
	}
	return result;
};

map <string, double> Graph::mod_table(map <string, double> table, Node current, Node to, vector <string> visited) {
	const string current_name = current.get("name");
	Node current_node = current;
	map <int, Path> current_paths = this->get_node_paths(current);
	map <int, Path>::iterator it = current_paths.begin();
	double smallest_weight = DBL_MAX;
	bool current_visited = false;
	for (; it != current_paths.end(); it++) {
		Path path = it->second;
		Node opposite_node = path.get_opposite(current);
		const string opposite_name = opposite_node.get("name");
		const double cur_length = path.get_weight() + table[current_name];
		const double table_value = table[opposite_name];
		bool opposite_visited = false;
		for (size_t i = 0; i < visited.size(); i++) {
			const string visited_name = visited[i];
			if (visited_name == opposite_name) {
				opposite_visited = true;
			}
			else if (visited_name == current_name) {
				current_visited = true;
			}
		}
		if (table_value > (double)cur_length) {
			table[opposite_name] = cur_length;
		}

		if (smallest_weight > cur_length && !opposite_visited) {
			smallest_weight = cur_length;
			current_node = opposite_node;
		}
	}

	visited.push_back(current_name);

	if (visited.size() == this->nodes.size() || current_visited) {
		const string to_name = to.get("name");
		return table;
	}
	else {
		return this->mod_table(table, current_node, to, visited);
	}
};