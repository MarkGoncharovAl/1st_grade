#include <iostream>
#include <vector>





template <typename T1, typename T2>
class Pair {
public:
    T1 first;
    T2 second;

    bool make_pair (T1 elem1, T2 elem2);
    bool make_pair (Pair elem);
    void print_pair ();
    void operator = (Pair elem);
};




template <typename T1, typename T2>
struct Node {
    Pair <T1, T2> val;
    struct Node * left;
    struct Node * right;
    bool full;
};




class container_of_iterators {
protected:
    static int** iterator_data;
    static size_t iterator_size;
};
size_t container_of_iterators::iterator_size = 0;
int** container_of_iterators::iterator_data = new int*[100];





template <typename T1, typename T2>
class Tree:public container_of_iterators {
private:

    Node <T1, T2> *main_tree;
    size_t size;

    Node <T1, T2> *create_Node ();
    void tree_insert (Node <T1, T2> *current_tree, Pair <T1, T2> new_pair);
    T2& tree_find (Node <T1, T2> *current_tree, T1 key);
    void tree_foreach (Node <T1, T2> *current_tree, void (*func)(T2* value));
    void tree_print (Node <T1, T2> *current_tree);
    bool tree_erase (Node <T1, T2>* current_tree, Node <T1, T2> *previous_tree, T1 key);
    //void tree_destroy (Node <T1, T2> *current_tree);

public:

    void insert (Pair <T1, T2> new_pair);
    void insert (T1 key, T2 value);
    void foreach (void (*func)(T2* value));
    void print ();
    size_t get_size ();
    T2& find (T1 key);
    bool erase (T1 key);
    size_t find_iterator (T2 value);
    //void destroy ();


    Tree ()
    {
        main_tree = new Node <T1, T2>[1];
        main_tree->left = NULL;
        main_tree->right = NULL;
        main_tree->full = false;
        iterator_size = 0;
        size = 0;
    }
    ~Tree()
    {
        delete[] container_of_iterators::iterator_data;
        //destroy();
    }
};









template <typename T2>
class Map_iterator:public container_of_iterators {
public:

    int current_iterator;

    Map_iterator <T2>& operator ++ ();
    T2& operator * ();
    bool operator != (Map_iterator <T2> other_iterator);
    bool operator == (Map_iterator <T2> other_iterator);

    Map_iterator()
    {
        current_iterator = -1;
    }
};








template <typename T1, typename T2>
class Map:public container_of_iterators {
public:

    Tree <T1, T2> tree;
    size_t size;

public:

    void insert (Pair <T1, T2> new_element);
    void insert (T1 elem1, T2 elem2);
    T2& find (T1 key);
    size_t get_size ();
    void print (T1 key);
    void full_print ();
    void foreach (void (*func)(T2* value));
    bool erase (T1 key);


    T2& operator [] (T1 key);
    T2& operator () (T1 key);
    void status ();

    Map ()
    {
        size = 0;
    }

    Map_iterator <T2> begin ();
    Map_iterator <T2> end ();
};



#include "Tree.cpp"
#include "Map.cpp"
