#pragma once
#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <functional>

namespace lib {

	//help functions
	inline void print_error_graph(std::string info, std::size_t LINE);
	inline void print_warning_graph(std::string info, std::size_t LINE);

	constexpr void* NODE_NOT_FOUND = nullptr;

	////////////////////////////////////////////
	//	Demands to TypeName and TypeData:
	//	1)constructor of copy
	//	2)constructor of moving
	//	3)default constructor 
	//	4)operator =
	//	5)operator ==
	//	6)operator <<
	////////////////////////////////////////////

	template <class TypeData,
		class TypeName = std::string>
		class Node
	{
	public:

		Node()                                                       noexcept;
		Node(const Node<TypeData, TypeName>& that)                   noexcept;
		Node(Node<TypeData, TypeName>&& that)                        noexcept;

		Node(const TypeName& init_name, const TypeData& init_data)   noexcept;
		Node(const TypeName& init_name, const TypeData& init_data, std::initializer_list<Node<TypeData, TypeName>*> next_nodes, std::initializer_list<Node<TypeData, TypeName>*> prev_nodes = std::initializer_list<Node<TypeData, TypeName>*>()) noexcept;

		void operator =     (const Node<TypeData, TypeName>& that)   noexcept;

		///////
		//	return data of Node
		///////
		TypeData GetData  ()                                   const noexcept { return data_; }

		///////
		//	return true if data is equal to your that_data
		///////
		bool     CheckData(const TypeData& that_data)          const noexcept { return data_ == that_data; }

		///////
		//	return name of Node
		///////
		TypeName GetName  ()                                   const noexcept { return name_; }

		///////
		//	return true if name is equal to your that_name 
		///////
		bool     CheckName(const TypeName& that_name)          const noexcept { return name_ == that_name; }

		///////
		//	Set new input data
		///////
		void     SetData  (const TypeData& new_data)                 noexcept { data_ = new_data; }

		///////
		//	Set new input namem but BE CAREFULL
		//	When you're creating new Node your new name is
		//	checking: Does Node exist that has the same name
		//	Now we haven't got other Node's data
		///////
		void     SetName  (const TypeName& new_name)                 noexcept { name_ = new_name; }

		///////
		//	return true if node was added (earlier wasn't)
		///////
		bool AddNextNeigh(Node<TypeData, TypeName>* new_neghboor)    noexcept;
		///////
		//	return true if node was added (earlier wasn't)
		///////
		bool AddPrevNeigh(Node<TypeData, TypeName>* new_neghboor)    noexcept;

		///////
		//	return true if node was added (earlier wasn't)
		///////
		bool AddNeigh    (Node<TypeData, TypeName>* new_neighboor)   noexcept { return AddNextNeigh(new_neighboor) && AddPrevNeigh(new_neighboor); }

		///////
		//	return true if node wasn't initialiazed yet
		///////
		bool IsEmpty     ()                                    const noexcept { return name_.empty(); }

		//For erasing memory of Node
		//Returns true if deleting was done properly
		//**************************************************************************
		bool EraseNextNeigh(Node<TypeData, TypeName>* that)          noexcept;
		bool ErasePrevNeigh(Node<TypeData, TypeName>* that)          noexcept;
		bool EraseAllPrev  ()                                        noexcept;
		bool EraseAllNext  ()                                        noexcept;
		bool EraseAll      ()                                        noexcept { return EraseAllNext() && EraseAllPrev(); }
		//**************************************************************************


		explicit operator bool()                               const noexcept { return !(name_.empty()); }

		///////
		//	print full information about Node
		///////
		void Dump() const noexcept;

		///////
		//	iterators of graph
		//	but prefer to use std::begin() and std::end()
		//	for (auto& node : graph) where
		//	node is std::unique_ptr<Node>
		///////
		auto cbegin_next() const noexcept { return next_nodes_.cbegin(); }
		auto cend_next  () const noexcept { return next_nodes_.cend(); }

		auto begin_next ()       noexcept { return next_nodes_.begin(); } //type == std::list<Node<TypeData>*>::iterator, but it doesn't match with begin()...
		auto end_next   ()       noexcept { return next_nodes_.end(); }

		auto cbegin_prev() const noexcept { return prev_nodes_.cbegin(); }
		auto cend_prev  () const noexcept { return prev_nodes_.cend(); }

		auto begin_prev ()       noexcept { return prev_nodes_.begin(); } //type == std::list<Node<TypeData>*>::iterator, but it doesn't match with begin()...
		auto end_prev   ()       noexcept { return prev_nodes_.end(); }

	private:
		TypeData                             data_;
		std::list<Node<TypeData, TypeName>*> next_nodes_;
		std::list<Node<TypeData, TypeName>*> prev_nodes_;
		TypeName                             name_;
	};




	template <class TypeNode,
		class TypeName = std::string>
		class Graph
	{
	public:
		Graph() noexcept :
			nodes_{}
		{}

		///////
		//	return true if function was done properly
		//	return false if name isn't empty
		///////
		bool 
			AddNode       (const TypeName& init_name, const TypeNode& init_data) noexcept;

		///////
		//	return true if function was done properly
		///////
		bool 
			AddNode       (const TypeName& init_name, const TypeNode& init_data, std::initializer_list<TypeName> next_neighboors, std::initializer_list<TypeName> prev_neighboors = std::initializer_list<TypeName>()) noexcept;

		///////
		//	return true if node was found and deleted
		///////
		bool 
			EraseNode     (const TypeName& name)                                noexcept;

		///////
		//	return true if nodes were found
		///////
		bool 
			EraseEdge     (const TypeName& cur_node, const TypeName& neighboor) noexcept;

		///////
		//	return true if nodes were found
		///////
		bool 
			EraseOrienEdge(const TypeName& cur_node, const TypeName& neighboor) noexcept;

		///////
		//	return nullptr if function wasn't done properly
		///////
		Node<TypeNode, TypeName>* 
			FindNode      (const TypeName& name)                                noexcept;

		///////
		//	return true if nodes were found
		///////
		bool 
			AddNeigh      (const TypeName& cur_node, const TypeName& neighboor) noexcept;

		///////
		//	return true if nodes were found
		///////
		bool AddNextNeigh (const TypeName& cur_node, const TypeName& neighboor) noexcept;

		///////
		//	Breadth-first search algorithm
		//	Output vector has name of Node and length to start_point Node
		///////
		std::vector<std::pair<TypeName, int>>
			BFS           (const TypeName& start_point, const std::function<void(Node<TypeNode, TypeName>*)>& func = [](Node<TypeNode, TypeName>*) {}) noexcept;

		///////
		//	So slow method of copying Graph
		///////
		void 
			operator =    (const Graph<TypeNode, TypeName>& that)               noexcept;

		///////
		//	print full information about graph
		///////
		void 
			Dump          () const noexcept;

		///////
		//	iterators of graph
		//	but prefer to use std::begin() and so on
		//	for (auto& node : graph) where
		//	node is std::unique_ptr<Node>
		///////
		auto cbegin() const noexcept { return nodes_.cbegin(); }
		auto cend  () const noexcept { return nodes_.cend(); }

		auto begin ()       noexcept { return nodes_.begin(); } //type == std::list<Node<TypeData>*>::iterator, but it doesn't match with begin()...
		auto end   ()       noexcept { return nodes_.end(); }

	private:
		std::vector
			<std::unique_ptr
				<Node<TypeNode, TypeName>> > nodes_;
	};
}




//Realization of struct methods NODE
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
template <class TypeData,
	      class TypeName>
lib::Node<TypeData, TypeName>::Node() noexcept :
	data_      {},
	next_nodes_{},
	prev_nodes_{},
	name_      {}
{}

template <class TypeData,
	      class TypeName>
lib::Node<TypeData, TypeName>::Node(const Node<TypeData, TypeName>& that) noexcept :
	data_      { that.data_ },
	next_nodes_{ that.next_nodes_ },
	prev_nodes_{ that.prev_nodes_ },
	name_      { that.name_ }
{}

template <class TypeData,
	      class TypeName>
lib::Node<TypeData, TypeName>::Node(Node<TypeData, TypeName>&& that) noexcept :
	data_      { std::move(that.data_) },
	next_nodes_{ std::move(that.next_nodes_) },
	prev_nodes_{ std::move(that.prev_nodes_) },
	name_      { std::move(that.name_) }
{}

template <class TypeData,
	      class TypeName>
lib::Node<TypeData, TypeName>::Node(const TypeName& init_name, const TypeData& init_data) noexcept :
	data_      { init_data },
	next_nodes_{},
	prev_nodes_{},
	name_      { init_name }
{}

template <class TypeData,
	      class TypeName>
lib::Node<TypeData, TypeName>::Node(const TypeName& init_name, const TypeData& init_data, std::initializer_list<Node<TypeData, TypeName>*> next_nodes, std::initializer_list<Node<TypeData, TypeName>*> prev_nodes/* = std::initializer_list<Node<TypeData, TypeName>*>()*/) noexcept :
	data_      { init_data },
	next_nodes_{ next_nodes },
	prev_nodes_{ prev_nodes },
	name_      { init_name }
{}

template <class TypeData,
	      class TypeName>
void lib::Node<TypeData, TypeName>::
	operator = (const Node<TypeData, TypeName>& that) noexcept
{
	data_ = that.data_;
	name_ = that.data_;
	next_nodes_ = that.next_nodes_;
	prev_nodes_ = that.prev_nodes_;
}




template <class TypeData,
	      class TypeName>
bool lib::Node<TypeData, TypeName>::
	AddNextNeigh(Node<TypeData, TypeName>* new_neghboor) noexcept
{
	if (new_neghboor == NODE_NOT_FOUND)
		return false;

	for (const auto& node : next_nodes_) {
		if (node == new_neghboor)
			return false;
	}
	next_nodes_.push_back(new_neghboor);
	new_neghboor->prev_nodes_.push_back(this);
	return true;
}

template <class TypeData,
	      class TypeName>
bool lib::Node<TypeData, TypeName>::
	AddPrevNeigh(Node<TypeData, TypeName>* new_neghboor) noexcept
{
	if (new_neghboor == NODE_NOT_FOUND)
		return false;

	for (const auto& node : prev_nodes_) {
		if (node == new_neghboor)
			return false;
	}
	prev_nodes_.push_back(new_neghboor);
	new_neghboor->next_nodes_.push_back(this);
	return true;
}

template <class TypeData,
	      class TypeName>
bool lib::Node<TypeData, TypeName>::
	EraseNextNeigh(Node<TypeData, TypeName>* that)         noexcept
{
	if (this == that)
		return false;

	for (auto iter = this->next_nodes_.cbegin(); iter != this->next_nodes_.cend(); ++iter) {
		if (*iter == that) {
			next_nodes_.erase(iter);

			for (auto new_iter = that->prev_nodes_.cbegin(); new_iter != that->prev_nodes_.cend(); ++new_iter) {
				if (*new_iter == this) {
					that->prev_nodes_.erase(new_iter);
					break;
				}
			}

			return true;
		}
	}
	return false;
}

template <class TypeData,
	      class TypeName>
bool lib::Node<TypeData, TypeName>::
	ErasePrevNeigh(Node<TypeData, TypeName>* that)        noexcept
{
	if (this == that)
		return false;

	for (auto iter = this->prev_nodes_.cbegin(); iter != this->prev_nodes_.cend(); ++iter) {
		if (*iter == that) {
			prev_nodes_.erase(iter);

			for (auto new_iter = that->next_nodes_.cbegin(); new_iter != that->next_nodes_.cend(); ++new_iter)
				if (*new_iter == this) {
					that->next_nodes_.erase(new_iter);
					break;
				}

			return true;
		}
	}
	return false;
}

template <class TypeData,
	      class TypeName>
bool lib::Node<TypeData, TypeName>::
	EraseAllPrev()                                       noexcept
{
	for (const auto& node : prev_nodes_) {
		for (auto iter = node->next_nodes_.cbegin(); iter != node->next_nodes_.cend(); ++iter) {
			if (*iter == this) {
				node->next_nodes_.erase(iter);
				break;
			}
		}
	}
	prev_nodes_.clear();
	return true;
}

template <class TypeData,
	      class TypeName>
bool lib::Node<TypeData, TypeName>::
	EraseAllNext()                                       noexcept
{
	for (const auto& node : next_nodes_) {
		for (auto iter = node->prev_nodes_.cbegin(); iter != node->prev_nodes_.cend(); ++iter) {
			if (*iter == this) {
				node->prev_nodes_.erase(iter);
				break;
			}
		}
	}
	next_nodes_.clear();
	return true;
}

template <class TypeData,
	      class TypeName>
void lib::Node<TypeData, TypeName>::
	Dump() const noexcept
{
	std::cout << "Current node: " << name_ << " has data: " << data_;
	std::cout << "\n\tPrevious nodes:\n\t";
	for (const auto& it : prev_nodes_)
		std::cout << it->name_ << ":\t" << it->data_ << "\n\t";
	std::cout << "\n\tNext nodes:\n\t";
	for (const auto& it : next_nodes_)
		std::cout << it->name_ << ":\t" << it->data_ << "\n\t";
	std::cout << std::endl;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//Realization GRAPH
//*********************************************************************
//*********************************************************************
template <class TypeNode,
	      class TypeName>
bool lib::Graph<TypeNode, TypeName>::
	AddNode(const TypeName& init_name, const TypeNode& init_data) noexcept
{
	if (FindNode(init_name) != nullptr)
		return false;
	std::unique_ptr<Node<TypeNode, TypeName>> new_node{ new Node<TypeNode, TypeName>{init_name, init_data} };
	nodes_.push_back(std::move(new_node));
	return true;
}

template <class TypeNode,
	      class TypeName>
bool lib::Graph<TypeNode, TypeName>::
	AddNode(const TypeName& init_name, const TypeNode& init_data, std::initializer_list<TypeName> next_neighboors, std::initializer_list<TypeName> prev_neighboors/* = std::initializer_list<TypeName>()*/) noexcept
{
	if (FindNode(init_name) != nullptr)
		return false;

	std::unique_ptr<Node<TypeNode, TypeName>> new_node{ new Node<TypeNode, TypeName>{init_name, init_data} };
	for (auto& name : next_neighboors) {
		Node<TypeNode, TypeName>* cur_node = this->FindNode(name);
		if (cur_node != nullptr)
			new_node.get()->AddNextNeigh(cur_node);
		else {
			print_error_graph("Can't create a new node!", __LINE__);
			return false;
		}
	}
	for (auto& name : prev_neighboors) {
		Node<TypeNode, TypeName>* cur_node = this->FindNode(name);
		if (cur_node != nullptr)
			new_node.get()->AddPrevNeigh(cur_node);
		else {
			print_error_graph("Can't create a new node!", __LINE__);
			return false;
		}
	}

	nodes_.push_back(std::move(new_node));
	return true;
}

template <class TypeNode,
	      class TypeName>
bool lib::Graph<TypeNode, TypeName>::
	EraseNode(const TypeName& name) noexcept
{
	Node<TypeNode, TypeName>* cur_node = this->FindNode(name);
	if (cur_node != nullptr) {
		cur_node->EraseAll();

		for (auto iter = nodes_.begin(); iter != nodes_.end() - 1; ++iter) {
			if (iter->get() == cur_node) {
				iter->swap(nodes_.at(nodes_.size() - 1));
			}
		}

		nodes_.pop_back();
		return true;
	}

	//cur_node == nullptr
	return false;
}

template <class TypeNode,
	      class TypeName>
bool lib::Graph<TypeNode, TypeName>::
	EraseEdge(const TypeName& cur_node, const TypeName& neighboor) noexcept
{
	Node<TypeNode, TypeName>* node_cur = this->FindNode(cur_node);
	Node<TypeNode, TypeName>* node_neig = this->FindNode(neighboor);

	if (node_cur == NODE_NOT_FOUND ||
		node_neig == NODE_NOT_FOUND)
		return false;

	node_cur->EraseNextNeigh(node_neig);
	node_cur->ErasePrevNeigh(node_neig);
	return true;
}

template <class TypeNode,
	      class TypeName>
bool lib::Graph<TypeNode, TypeName>::
	EraseOrienEdge(const TypeName& cur_node, const TypeName& neighboor) noexcept
{
	Node<TypeNode, TypeName>* node_cur = this->FindNode(cur_node);
	Node<TypeNode, TypeName>* node_neig = this->FindNode(neighboor);

	if (node_cur == NODE_NOT_FOUND ||
		node_neig == NODE_NOT_FOUND)
		return false;

	node_cur->EraseNextNeigh(node_neig);
	return true;
}

template <class TypeNode,
	      class TypeName>
lib::Node<TypeNode, TypeName>* lib::Graph<TypeNode, TypeName>::
	FindNode(const TypeName& name) noexcept
{
	for (auto node = nodes_.cbegin(); node != nodes_.cend(); ++node) {
		if ((*node)->CheckName(name))
			return node->get();
	}
	return nullptr;
}

template <class TypeNode,
	      class TypeName>
bool lib::Graph<TypeNode, TypeName>::
	AddNeigh(const TypeName& cur_node, const TypeName& neighboor) noexcept
{
	Node<TypeNode, TypeName>* node_cur = this->FindNode(cur_node);
	Node<TypeNode, TypeName>* node_neig = this->FindNode(neighboor);

	if (node_cur == NODE_NOT_FOUND ||
		node_neig == NODE_NOT_FOUND)
		return false;

	node_cur->AddNextNeigh(node_neig);
	node_cur->AddPrevNeigh(node_neig);
	return true;
}

template <class TypeNode,
	      class TypeName>
bool lib::Graph<TypeNode, TypeName>::
	AddNextNeigh(const TypeName& cur_node, const TypeName& neighboor) noexcept
{
	Node<TypeNode, TypeName>* node_cur = this->FindNode(cur_node);
	Node<TypeNode, TypeName>* node_neig = this->FindNode(neighboor);

	if (node_cur == NODE_NOT_FOUND ||
		node_neig == NODE_NOT_FOUND)
		return false;

	node_cur->AddNextNeigh(node_neig);
	return true;
}

template <class TypeNode,
	      class TypeName>
std::vector<std::pair<TypeName, int>> 
	lib::Graph<TypeNode, TypeName>::
	BFS(const TypeName& start_point, const std::function<void(Node<TypeNode, TypeName>*)>& func/* = [](Node<TypeNode, TypeName>*) {}*/) noexcept
{
	constexpr int NOT_USED = -1;

	if (FindNode(start_point) == nullptr)
		return std::move(std::vector<std::pair<TypeName, int>>());

	//start_point is existing now!!!;
	Graph<TypeNode, TypeName> graph;
	graph = *this;

	std::queue<Node<TypeNode, TypeName>*> queue;
	for (auto& node : graph)
	{
		if (node->CheckName(start_point)) {
			node->SetData(0);
			func(this->FindNode(node->GetName()));
			queue.push(node.get());
		}
		else
			node->SetData(NOT_USED);
	}

	while (!queue.empty()) {
		Node<TypeNode, TypeName>* cur_node = queue.front();
		queue.pop();

		for (auto& elem : *cur_node) {
			if (elem->CheckData(NOT_USED)) {
				elem->SetData(cur_node->GetData() + 1);
				func(this->FindNode(elem->GetName()));
				queue.push(elem);
			}
		}
	}

	std::vector<std::pair<TypeName, int>> answer;
	for (const auto& node : graph) {
		answer.push_back(std::move(std::make_pair(node->GetName(), node->GetData())));
	}
	return std::move(answer);
}

template <class TypeNode,
	      class TypeName>
void lib::Graph<TypeNode, TypeName>::
	operator = (const Graph<TypeNode, TypeName>& that) noexcept
{
	nodes_.clear();
	for (const auto& it : that.nodes_) {
		std::unique_ptr<Node<TypeNode, TypeName>> new_node(new Node<TypeNode, TypeName>);
		new_node->SetData(it->GetData());
		new_node->SetName(it->GetName());
		nodes_.push_back(std::move(new_node));
	}

	auto begin = nodes_.begin();
	auto begin_that = that.cbegin();

	while (begin != nodes_.end()) {
		for (auto it = (*begin_that)->cbegin_next(); it != (*begin_that)->cend_next(); ++it) {
			(*begin)->AddNextNeigh(FindNode((*it)->GetName()));
		}
		for (auto it = (*begin_that)->cbegin_prev(); it != (*begin_that)->cend_prev(); ++it) {
			(*begin)->AddPrevNeigh(FindNode((*it)->GetName()));
		}
		begin++;
		begin_that++;
	}
}

template <class TypeNode,
	      class TypeName>
void lib::Graph<TypeNode, TypeName>::
	Dump() const noexcept
{
	std::cout << "Dump is starting!\n";
	for (auto iter = nodes_.cbegin(); iter != nodes_.cend(); ++iter) {
		iter->get()->Dump();
	}
}
//*********************************************************************
//*********************************************************************


//Help functions
//---------------------------------------------------------------------
//---------------------------------------------------------------------
namespace std
{
	template <class T,
		      class U>
	inline auto begin(const lib::Node<T, U>& node)
	{
		return node.cbegin_next();
	}

	template <class T,
		      class U>
	inline auto end(const lib::Node<T, U>& node)
	{
		return node.cend_next();
	}

	template <class T,
		      class U>
	inline auto begin(const lib::Graph<T, U>& graph)
	{
		return graph.cbegin();
	}

	template <class T,
	 	      class U>
	inline auto end(const lib::Graph<T, U>& graph)
	{
		return graph.cend();
	}
}

 void lib::print_error_graph  (std::string info, std::size_t LINE)
{
	std::cout << std::endl << info << std::endl;
	printf("Mistake was found in line %ld\n", LINE);
	std::exit(EXIT_FAILURE);
}
 void lib::print_warning_graph(std::string info, std::size_t LINE)
{
	std::cout << std::endl << info << std::endl;
	printf("Warning was found in line %ld\n", LINE);
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------