#include "tree.h"

Node Tree::add_node(string name, string value, int level, vector <Node> parents) {
	const size_t parents_size = parents.size();
	for (size_t i = 0; i < names.size(); i++) {
		const string it_name = names[i];
		if (it_name == name)
			throw("Error, node with name " + name + " already exists");
	}
	if (level > 1 && !parents_size) {
		throw("Error, nodes on level 2 and higher must have at least one parent");
	}
	else {
		Node node(name, value, level, parents);

		for (size_t i = 0; i < parents.size(); i++) {
			Node parent = parents[i];
			const int parent_level = stoi(parent.get("level"));
			if (parent_level < level)
				throw("Error, parent level cannot be smaller than child's");
			else
				parent.add_child(node);
		}

		if (structure.count(level)) {
			structure[level].push_back(node);
		}
		else {
			vector <Node> node_vector = { node };
			auto result = structure.emplace(level, node_vector);
		}

		names.push_back(name);
		levels = structure.size();
		vector <Node> nnn = get_all_nodes();
		return node;
	};

};

map <int, vector <Node>> Tree::remove_node(Node node) {
	const string name = node.get("name");
	const int level = stoi(node.get("level"));
	for (size_t i = 0; i < names.size(); i++) {
		const string cur_name = names[i];
		if (cur_name == name) {
			names.erase(names.begin() + i);
			break;
		}
	}

	vector <Node>& nodesRef = structure[level];
	for (size_t i = 0; i < nodesRef.size(); i++) {
		Node cur_node = nodesRef[i];
		const string cur_name = cur_node.get("name");
		if (cur_name == name) {
			vector <Node> children = cur_node.get_children();
			for (size_t k = 0; k < children.size(); k++) {
				Node child = children[k];
				const size_t parents_size = child.get_parents().size();
				if (!parents_size - 1)
					children_to_remove.push_back(child);
			}

			vector <Node> parents = cur_node.get_parents();
			for (size_t k = 0; k < parents.size(); k++) {
				Node parent = parents[k];
				parent.remove_child(cur_node);
			}

			nodesRef.erase(nodesRef.begin() + i);
			auto it = structure.find(level);
			if (!nodesRef.size() && it != structure.end())
				structure.erase(it);
			levels = (int)structure.size();
			break;
		}
	}

	const size_t objects_to_remove = children_to_remove.size();
	if (objects_to_remove) {
		Node child_to_remove = children_to_remove.back();
		children_to_remove.pop_back();
		return remove_node(child_to_remove);
	}
	else {
		return structure;
	}
};

map <int, vector <Node>> Tree::remove_node(string name) {
	Node node = this->get_node(name);
	const int level = stoi(node.get("level"));
	for (size_t i = 0; i < names.size(); i++) {
		const string cur_name = names[i];
		if (cur_name == name) {
			names.erase(names.begin() + i);
			break;
		}
	}

	vector <Node> &nodesRef = structure[level];
	for (size_t i = 0; i < nodesRef.size(); i++) {
		Node cur_node = nodesRef[i];
		const string cur_name = cur_node.get("name");
		if (cur_name == name) {
			vector <Node> children = cur_node.get_children();
			for (size_t k = 0; k < children.size(); k++) {
				Node child = children[k];
				const size_t parents_size = child.get_parents().size();
				if (!parents_size - 1)
					children_to_remove.push_back(child);
			}

			vector <Node> parents = cur_node.get_parents();
			for (size_t k = 0; k < parents.size(); k++) {
				Node parent = parents[k];
				parent.remove_child(cur_node);
			}

			nodesRef.erase(nodesRef.begin() + i);
			auto it = structure.find(level);
			if (!nodesRef.size() && it != structure.end())
				structure.erase(it);
			levels = (int)structure.size();
			break;
		}
	}

	const size_t objects_to_remove = children_to_remove.size();
	if (objects_to_remove) {
		Node child_to_remove = children_to_remove.back();
		children_to_remove.pop_back();
		return remove_node(child_to_remove);
	}
	else {
		return structure;
	}
};

vector <Node> Tree::get_all_nodes() {
	vector <Node> result;
	map <int, vector<Node> >::iterator it = structure.begin();
	for (; it != structure.end(); it++) {
		vector <Node> nodes = it->second;
		for (size_t i = 0; i < nodes.size(); i++) {
			Node node = nodes[i];
			result.push_back(node);
		}
	}
	return result;
};

string Tree::get_level_info(int level) {
	vector <Node> nodes = get_all_nodes();
	string level_str = "Current level: " + to_string(level);
	string nodes_at_level = "Nodes at current level: " + to_string(nodes.size());
	string node_list = "Nodes: {";
	for (size_t i = 0; i < nodes.size(); i++) {
		Node node = nodes[i];
		const string node_name = node.get("name");
		node_list += "\"" + node_name + "\"";
		if (i != nodes.size() - 1)
			node_list += ", ";
	}
	node_list += "}";
	return level_str + "\n" + nodes_at_level + "\n" + node_list + "\n";
};

string Tree::get_level_info(string level) {
	vector <Node> nodes = get_all_nodes();
	string level_str = "Current level: " + level;
	string nodes_at_level = "Nodes at current level: " + to_string(nodes.size());
	string node_list = "Nodes: {";
	for (size_t i = 0; i < nodes.size(); i++) {
		Node node = nodes[i];
		const string node_name = node.get("name");
		node_list += "\"" + node_name + "\"";
		if (i != nodes.size() - 1)
			node_list += ", ";
	}
	node_list += "}";
	return level_str + "\n" + nodes_at_level + "\n" + node_list + "\n";
};