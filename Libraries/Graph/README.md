# Graph #

### Convenient struct for work with graphes ###

When you work with graphes, you always have to write structures such as Node, Graph and so on. I've tried to solve this problem. This library isn't as good as I dreamt before project - it concerned with: there are many different types of graph tasks and it's so hard to realize common structure. But this solution could help you in 70-80% cases (my experience), it's as not bad as it could be)

### Templates ###

lib::Graph <TypeNode, TypeName = std::string>. Demands to this templates:
*	default, copy and moving constructors
*	operators =, ==, <<

### Inner data ###
Graph has private
*	##### std::vector <std::unique_ptr <Node<TypeNode, TypeName>> > nodes_; #####
Every Node has private

*	##### TypeData                             data_;
*	##### std::list<Node<TypeData, TypeName>*> next_nodes_;
*	##### std::list<Node<TypeData, TypeName>*> prev_nodes_;
*	##### TypeName                             name_;

### Functions: Node ###
Read comments below function and you will find the destination of this function. Moreovere you can check .h - It's so easy to understand

*	Get, Set, Check functions with data and name of Node. SetName() is dangerous  be carefull - read comments!
*	AddNeigh(Node*), AddNextNeigh(Node*), AddPrevNeigh(Node*) - everything is clear
*	Erase edges
*	Dump() - printing full info about this Node

### Functions: Graph ###
*	AddNode(TypeName, TypeNode, NextNodes, PrevNodes) - if you want you can not to define neighboors, do this later!
*	EraseNode, EraseEdge, EraseOrienEdge
*	FindNode(TypeName) - returns Node*, it helps to operate with defined Node
*	##### BFS(TypeName start_node, std::function<void(Node<TypeName, TypeNode>*)> = [](Node<TypeName, TypeNode>*){}) 
	Breadth-first-search algorithm that can do function with every Node and returns std::vector<std::pair<TypeName, int>> - shows what's the min-length from start_node to this. Shows -1 if you can't go to this Node from start_node 

### Iterators ###
##### lib::Graph #####
Graph has begin(), cbegin(), std::begin(), std::end(), BUT - iterators shows you data to std::unique_ptr<Node>. I didn't want to create another std::vector that contains Node* - useless using memory)

//auto == std::unique_ptr<Node>

for (const auto& elem : graph)
##### lib::Node #####
Node has begin_next(), begin_prev(), cbegin_next() and so on. Iterators now show you data to Node*

//auto == Node*

for (const auto& elem : node) 

//in this using elem belongs to next_nodes!!!

### Good luck! ###
