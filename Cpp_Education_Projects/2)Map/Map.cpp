template <typename T2>
Map_iterator <T2>& Map_iterator <T2>::operator ++ ()
{
    current_iterator++;
    return (*this);
}
template <typename T2>
T2& Map_iterator <T2>::operator * ()
{
    if (current_iterator < 0) {
        T2 *trash = new T2;
        return (*trash);
    }
    return (*((T2*)(this->iterator_data)[current_iterator]));
}
template <typename T2>
bool Map_iterator <T2>::operator != (Map_iterator <T2> other_iterator)
{
    if (this->iterator_data[current_iterator] == this->iterator_data[other_iterator.current_iterator]) {
        return false;
    }
    return true;
}
template <typename T2>
bool Map_iterator <T2>::operator == (Map_iterator <T2> other_iterator)
{
    if (this->iterator_data[current_iterator] == this->iterator_data[other_iterator.current_iterator])
        return true;
    return false;
}










template <typename T1, typename T2>
void Map <T1, T2>::insert (Pair <T1, T2> new_element)
{
    tree.insert (new_element);
    size++;
}
template <typename T1, typename T2>
void Map <T1, T2>::insert (T1 elem1, T2 elem2)
{
    tree.insert(elem1, elem2);
    size++;
}
template <typename T1, typename T2>
T2& Map <T1, T2>::find(T1 key)
{
    return (tree.find(key));
}
template <typename T1, typename T2>
size_t Map <T1, T2>::get_size ()
{
    return size;
}
template <typename T1, typename T2>
void Map <T1, T2>::print (T1 key)
{
    T2 finding_value;
    bool check = tree.find(key, &finding_value);
    if (check)
        std::cout << finding_value << std::endl;
    else
        std::cout << "OBJECT WASN'T FOUND\n";
}
template <typename T1, typename T2>
void Map <T1, T2>::full_print ()
{
    tree.print ();
}
template <typename T1, typename T2>
void Map <T1, T2>::foreach (void (*func)(T2* value))
{
    tree.foreach (func);
}
template <typename T1, typename T2>
bool Map <T1, T2>::erase (T1 key)
{
    return (tree.erase(key));
}
template <typename T1, typename T2>
T2& Map <T1, T2>::operator [] (T1 key)
{
    return tree.find(key);
}
template <typename T1, typename T2>
T2& Map <T1, T2>::operator () (T1 key)
{
    T2 *checking = new T2;
    T2 *output = &(tree.find(key));

    if (*checking == *output) {
        tree.insert (key, *output);
        return (tree.find(key));
    }
    delete checking;
    return (*output);
}
template <typename T1, typename T2>
Map_iterator <T2> Map <T1, T2>::begin ()
{
    Map_iterator <T2> *new_iterator = new Map_iterator <T2>;
    new_iterator->current_iterator = 0;
    return (*new_iterator);
}
template <typename T1, typename T2>
Map_iterator <T2> Map <T1, T2>::end ()
{
    Map_iterator <T2> *new_iterator = new Map_iterator <T2>;
    new_iterator->current_iterator = this->iterator_size;
    return (*new_iterator);
}
