template <typename T1, typename T2>
bool Pair <T1, T2>::make_pair (T1 elem1, T2 elem2)
{
    try {
        first = elem1;
        second = elem2;
    }
    catch (const std::exception& ex) {
        std::cout << "Misake in using \"make_pair\"\n";
        return false;
    }

    return true;
}
template <typename T1, typename T2>
bool Pair <T1, T2>::make_pair (Pair elem)
{
    try {
        first = elem.first;
        second = elem.second;
    }
    catch (const std::exception& ex) {
        std::cout << "Misake in using \"make_pair\"\n";
        return false;
    }
    return true;
}
template <typename T1, typename T2>
void Pair <T1, T2>::print_pair ()
{
    std::cout << "First: \"" << first << "\"\tSecond: \"" << second  << "\"\n";
}
template <typename T1, typename T2>
void Pair <T1, T2>::operator = (Pair elem)
{
    first = elem.first;
    second = elem.second;
}







template <typename T1, typename T2>
Node <T1, T2> *Tree<T1, T2>::create_Node ()
{
    Node <T1, T2>* new_Node = new Node <T1, T2>;
    new_Node->left = NULL;
    new_Node->right = NULL;
    new_Node->full = false;
    return new_Node;
}
template <typename T1, typename T2>
void Tree <T1, T2>::tree_insert (Node <T1, T2> *current_tree, Pair <T1, T2> new_pair)
{
    if (current_tree->left == NULL && current_tree->right == NULL && current_tree->full == false) {
        (current_tree->val).make_pair (new_pair);

        this->iterator_data[this->iterator_size] = (int*)(&((current_tree->val).second));
        (this->iterator_size)++;
        this->iterator_data[this->iterator_size] = nullptr;

        current_tree->full = true;
        size++;
        return;
    }

    if (new_pair.first > current_tree->val.first) {
        if (current_tree->right == NULL)
            current_tree->right = create_Node();

        tree_insert (current_tree->right, new_pair);
        return;
    }
    if (new_pair.first < current_tree->val.first) {
        if (current_tree->left == NULL)
            current_tree->left = create_Node ();

        tree_insert (current_tree->left, new_pair);
        return;
    }
    if (new_pair.first == current_tree->val.first) {
        current_tree->val = new_pair;
        return;
    }
}
template <typename T1, typename T2>
T2& Tree <T1, T2>::tree_find (Node <T1, T2> *current_tree, T1 key)
{
    if (current_tree->val.first == key)
        return current_tree->val.second;

    if (current_tree->val.first > key && current_tree->left != NULL)
        return tree_find(current_tree->left, key);

    if (current_tree->val.first < key && current_tree->right != NULL)
        return tree_find(current_tree->right, key);


    T2* trash = new T2;
    return (*trash);
}
template <typename T1, typename T2>
void Tree <T1, T2>::tree_foreach (Node <T1, T2> *current_tree, void (*func)(T2* value))
{
    if (current_tree->left == NULL && current_tree->right == NULL) {
        if (current_tree->full)
            func (&current_tree->val.second);
        return;
    }
    if (current_tree->left != NULL)
        tree_foreach (current_tree->left, func);

    func (&current_tree->val.second);

    if (current_tree->right != NULL)
        tree_foreach (current_tree->right, func);
}
/*template <typename T1, typename T2>
void Tree <T1, T2>::destroy ()
{
     tree_destroy(main_tree);
}
template <typename T1, typename T2>
void Tree <T1, T2>::tree_destroy (Node <T1, T2> *current_tree)
{
    if (current_tree->left != NULL)
        tree_destroy (current_tree->left);

    if (current_tree->right != NULL)
        tree_destroy (current_tree->right);

    delete current_tree;
}*/
template <typename T1, typename T2>
void Tree <T1, T2>::tree_print (Node <T1, T2> *current_tree)
{
    if (current_tree->left == NULL && current_tree->right == NULL) {
        if (current_tree->full)
            current_tree->val.print_pair();
        return;
    }
    if (current_tree->left != NULL)
        tree_print (current_tree->left);

    current_tree->val.print_pair ();

    if (current_tree->right != NULL)
        tree_print (current_tree->right);
}
template <typename T1, typename T2>
void Tree <T1, T2>::foreach (void (*func)(T2* value))
{
    tree_foreach (main_tree, func);
}
template <typename T1, typename T2>
void Tree <T1, T2>::insert (Pair <T1, T2> new_pair)
{
    tree_insert(main_tree, new_pair);
}
template <typename T1, typename T2>
void Tree <T1, T2>::insert (T1 key, T2 value)
{
    Pair <T1, T2> new_pair;
    new_pair.make_pair(key, value);
    tree_insert(main_tree, new_pair);
}
template <typename T1, typename T2>
void Tree <T1, T2>::print ()
{
    tree_print (main_tree);
}
template <typename T1, typename T2>
size_t Tree <T1, T2>::get_size ()
{
    return size;
}
template <typename T1, typename T2>
T2& Tree <T1, T2>::find (T1 key)
{
    return tree_find (main_tree, key);
}
template <typename T1, typename T2>
bool Tree <T1, T2>::tree_erase (Node <T1, T2> *current_tree, Node <T1, T2> *previous_tree, T1 key)
{
    if (key < (current_tree->val).first) {
        if (current_tree->left == NULL)
            return false;
        return (tree_erase (current_tree->left, current_tree, key));
    }
    if (key > (current_tree->val).first) {
        if (current_tree->right == NULL)
            return false;
        return (tree_erase (current_tree->right, current_tree, key));
    }


    if ((current_tree->val).first == key) {

        size_t current_iterator = find_iterator((current_tree->val).second);
        if (current_iterator == this->iterator_size - 1) {
            (this->iterator_size)--;
            this->iterator_data[iterator_size] = nullptr;
        }
        else {
            this->iterator_data[current_iterator] = this->iterator_data[this->iterator_size - 1];
            iterator_size--;
            this->iterator_data[this->iterator_size] = nullptr;
        }

        if (current_tree->right != NULL) {
            Node <T1, T2> *deleting_Node = current_tree->right;
            while (deleting_Node->left != nullptr)
                deleting_Node = deleting_Node->left;

            current_tree->val = deleting_Node->val;

            if (current_tree->right == deleting_Node) {
                current_tree->right = deleting_Node->right;
                return true;
            }

            Node <T1, T2> *parent_deleting = current_tree->right;
            while (parent_deleting->left != deleting_Node)
                parent_deleting = parent_deleting->left;
            parent_deleting->left = deleting_Node->right;

            return true;
        }

        if (current_tree->left != nullptr) {
            current_tree->val = current_tree->left->val;
            current_tree->right = current_tree->left->right;
            current_tree->left = current_tree->left->left;
            return true;
        }

        if (previous_tree == nullptr) {
            current_tree->full = false;
            return true;
        }
        if (previous_tree->left == current_tree)
            previous_tree->left = NULL;
        if (previous_tree->right == current_tree)
            previous_tree->right = NULL;
    }

    return false;
}
template <typename T1, typename T2>
bool Tree <T1, T2>::erase (T1 key)
{
    return (tree_erase (main_tree, nullptr, key));
}
template <typename T1, typename T2>
size_t Tree <T1, T2>::find_iterator (T2 value)
{
    size_t num = 0;
    while (value != *((T2*)(this->iterator_data[num])) && num < this->iterator_size)
        num++;

    if (num == this->iterator_size)
        return -1;
    return num;
}
