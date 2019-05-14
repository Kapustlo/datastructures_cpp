#include "node.h"

Node::Node() {
	vector <Node> empty_vector;

	this->name = "";
	this->value = "";
	this->level = -1;
	this->ancestors = this->parents = this->children = empty_vector;
};

Node::Node(string name, string value, int level, vector <Node> parents) {
	this->name = name;
	this->value = value;
	this->level = level;
	this->parents = parents;
	this->ancestors = parents;
	for (size_t i = 0; i < this->parents.size(); i++) {
		Node parent = this->parents[i];
		this->ancestors.push_back(parent);
		vector <Node> ancestors = parent.get_ancestors();
		for (size_t k = 0; k < ancestors.size(); k++) {
			Node ancestor = ancestors[k];
			this->ancestors.push_back(ancestor);
		}
	}
};

string Node::get(string attribute) {
	if (attribute == "name")
		return this->name;
	else if (attribute == "value")
		return this->value;
	else if (attribute == "level")
		return to_string(this->level);
	else
		return "Attribute does not exist";
};

int Node::increase_level(int value) {
	this->level += value;
	return this->level;
};

void Node::set_level(int level) {
	this->level = level;
};

vector <Node> Node::add_child(Node node) {
	this->children.push_back(node);
	return this->children;
};

vector <Node> Node::add_parent(Node node) {
	this->parents.push_back(node);
	return this->parents;
};

// PROTECTED

vector <Node> Node::remove_child(Node node) {
	const string node_name = node.get("name");
	vector <Node> children = this->children;
	for (size_t i = 0; i < children.size(); i++) {
		Node child = children[i];
		const string child_name = child.get("name");
		if (child_name == node_name) {
			children.erase(children.begin() + i);
			return children;
		}
	}
};

vector <Node> Node::remove_child(string node_name) {
	vector <Node> children = this->children;
	for (size_t i = 0; i < children.size(); i++) {
		Node child = children[i];
		const string child_name = child.get("name");
		if (child_name == node_name) {
			children.erase(children.begin() + i);
			return children;
		}
	}
};