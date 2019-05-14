Including files
===============

``` c++
#include <datastructures\datastructures.h>
#include <datastructures\utils\longeststring.h>
```
Library utils
=============

Getting the length of the longest string in the array
-----------------------------------------------------

``` c++
string strings[] = {"20","1","100"};

int longest_string = longest_string_value(strings, 3);

cout << longest_string << endl;

>> 3
```

or

``` c++

vector <string> strings = {"20","1","100"};

int longest_string = longest_string_value(strings);

cout << longest_string << endl;

>> 3
```
Library datastructures
======================
```c++
#include "datastructures\datastructures.h"
```
Class Node
----------
### Constructor
``` c++
Node node(string name, string value="", int level = -1, vector <Node> parents={});
/*
name - name of the node
value - value of the node is string but meant for numbers so keep it in mind and convert it into something else if needed
level - level on which the node is located
parents - ...
*/
```
### Public methods
``` c++
string attr = node.get(string param); // Possible params: name, level, value if passed something else returns "Attribute does not exist"

vector <Node> children = node.get_children();
vector <Node> parents = node.get_parents();
vector <Node> ancestors = node.get_ancestors();

// ALL NODE METHODS BELOW ARE PUBLIC BUT MENT FOR INTERNAL USE ONLY, PLEASE DO NOT CALL THEM YOURSELF
int new_level = node.increase_level(int value); // Returns the new level of the node
node.set_level(int level);

vector <Node> new_children = node.add_child(Node node); // Returns vector of all children
vector <Node> new_parents = node.add_parent(Node node); // Returns vector of all parents

vector <Node> r_children = node.remove_child(Node node); // Returns children left
// or
vector <Node> r_children = node.remove_child(string name);
```
Class Path
----------
### Constructor:
``` c++
Path path(Node first, Node second, double weight);
```

or

``` c++
Path path(Node nodes[], double weight);
```
or

``` c++
Path path(vector <Node> nodes, double weight);
```

### Public methods:
#### Opposite node
``` c++
// Pass a node object and get its opposite from the path
Node opposite_node = path.get_opposite(Node node); // Returns the opposite node in the path
```
or 
``` c++
// Pass the name of a node and get its opposite in the path if the give node is not in the path throws error
Node opposite_node = path.get_opposite(string name); // Returns the opposite node in the path
```
#### In path
``` c++
// Pass a node object
bool is_in_path = path.in_path(Node node);
```
or
``` c++
// Pass a node's name
bool is_in_path = path.in_path(string name);
```

#### Other methods
``` c++
pair <Node, Node> nodes_in_path = path.get_nodes();
double path_weight = path.get_weight();
```
Class Graph
-----------
### Constructor:
``` c++
Graph graph();
```
### Private methods:
#### Get all paths related to a node
``` c++
// Returns map with current index values as keys and path objects as values
map <int, Path> node_paths = graph.get_node_paths(Node node);
```
or
``` c++
map <int, Path> node_paths = graph.get_node_paths(string name); # Pass a node's name
```
### Modyfying a table of distances
``` c++
// Modifies a table of the shortest distances beetwen the start adn the end 
// Used in public method get_distance()
map <string, double> mod_table(map <string, double> table, Node current, Node to, vector <string> visited = {});
```
### Public methods:
#### Working with nodes
``` c++
Node node = graph.get_node(string name); // Returns a node object from the graph

// Creates, returns a new node and adds it into the graph
Node new_node = grapg.add_node(string name, string value="");

// Created, returns and adds a new path into the graph
Path new_path = graph.connect_nodes(Node first, Node second, double weight); 

// or

Path new_path = graph.connect_nodes(string first, string second, double weight);

vector <Path> r_nodes = graph.remove_node(string name); // Removes a node and returns a vector of the remained ones

// or 

vector <Path> r_nodes = graph.remove_node(Node node);

// Returns a stringified visualisation of paths in the graph in format {"Node A"} <---> {"Node B"}
```
### Other methods:
``` c++
string s_paths = graph.get_paths();

double distance = graph.get_distance(Node from, Node to); // Returns the shortest distance between two nodes

// or 

double distance = graph.get_distance(string from, string to);
```

Class Tree
-----------
### Constructor:
``` c++
Tree tree();
```

### Public methods:
#### Working with nodes:
``` c++
// Creates, returns and adds a new node into the tree
Node new_node = tree.add_node(string name, string value, int level = 1, vector <Node> parents = {});

// Returns current tree structure
map <int, vector <Node>> st = tree.remove_node(string name);

// or 

map <int, vector <Node>> st = tree.remove_node(Node node);

```
### Tree information
``` c++
vector <Node> l_nodes = tree.get_all_nodes_at_level(int level);
vector <Node> all_nodes = tree.get_all_nodes();

/*
Returns stringified information about a level in format:
Level: 1
Nodes at level: 1
Nodes: {"A"}
*/

string level_info = tree.get_level_info(string level);

// or 

string level_info = tree.get_level_info(int level);
```
