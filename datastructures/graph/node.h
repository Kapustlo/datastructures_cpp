#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>

using namespace std;

class Node {
private:
	string name, value;
	vector <Node> ancestors;
	vector <Node> parents;
	vector <Node> children;
	int level;
public:
	Node();

	Node(string name, string value = "", int level = -1, vector <Node> parents = {});

	string get(string attribute);

	vector <Node> get_children() {
		return this->children;
	};

	vector <Node> get_parents() {
		return this->parents;
	};

	vector <Node> get_ancestors() {
		return this->ancestors;
	};


	int increase_level(int increment);

	int set_level(int level);

	vector <Node> add_child(Node node);
	
	vector <Node> add_parent(Node node);

	vector <Node> remove_child(Node node);
	vector <Node> remove_child(string node_name);
};

#endif