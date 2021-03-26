#pragma once
#include "Constants.h"
#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>

#ifdef DEBUG
	#define DEBUG_PRINT_0 std::cout << "\t!\n"
	#define DEBUG_PRINT_1(a) std::cout << a << std::endl
	#define DEBUG_PRINT_2(a,b) std::cout << a << "\t" << b << std::endl
#else
	#define DEBUG_PRINT_0
	#define DEBUG_PRINT_1	
	#define DEBUG_PRINT_2
#endif // DEBUG


class Node {

public:
	
	Node();
	explicit Node(Node* new_parent);
	explicit Node(Type new_type, double new_value);
	explicit Node(Type new_type, double new_value, Node* new_parent);

	void fill_Node(Type new_type, double new_value);
	void fill_Node(Type new_type, double new_value, Node* new_parent);
	void copy_data(const Node* other_Node);
	
	Type get_type() const { return type_; }
	double get_value() const { return value_; }
	bool is_full() const { if (type_ == Type::Empty) return false; return true; }

private:

	Type type_;
	double value_;

	Node* parent_;
	Node* left_;
	Node* right_;

	friend class Tree;
};



class Tree {
public:

	Tree();
	~Tree();

	size_t get_size() const { return size_; }
	double get_dif_var() const { return dif_var_; }
	Node* get_main_Node() const { return main_Node_; }

	void print() const;

	void read_string_to_Tree(const char* current_symbol);

	void dif(const Tree& original);
	double operator() (double* variables) const;

private:

	Node* main_Node_;
	size_t size_;
	double dif_var_;

	std::vector <Tree*> SavingTrees;


	Node* read_string_to_Tree(Node* current_Node, const char*& current_symbol);
	bool is_safe(double* variables) const;

	void print(Node* current_Node) const;
	void print_element(Node* current_Node) const;

	Node* dif(Node* current_Node, const Node* original_Node);
	double get_answer(const Node* current_Node, const double* variables) const;
	double safechecking_get_answer(const Node* current_Node, bool& safe, double* variables) const;

	void simplify_tree(Node* current_Node);
	void create_saving_tree(Node* dangerous_main_Node);

	Node* copy_tree(Node* current_Node, const Node* original_Node);
	bool compare_trees(Node* first_tree, Node* second_tree);
	//void swap_Nodes(Node* left_Node, Node* right_Node);

	void destroy_under_Node(Node* current_Node);
	void destroy_one_Node(Node* current_Node);
	void destroy(Node* current_Node);

};

