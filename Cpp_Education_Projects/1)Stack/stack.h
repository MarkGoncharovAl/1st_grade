#include <iostream>
#include <fstream>

std::ofstream pushfile("pushfile.txt");

const char ORDINARY_CASE = '0';
const char Warning_useless_function = 'A';
const char Warning_small_size = 'B';
const char SMALL_CAP = 'a';
const char EMPTY_STACK = 'b';
const char FULL_STACK = 'c';
const char NO_DATA = 'd';
const char MEMORY_PROBLEM = 'e';
const char NULL_PTR = 'f';

template <typename T>
class Stack
{
    private: T *Data;
    private: size_t Size;
    private: size_t Cap;
    private: char status;

    public:
        void init (int Capacity);  // use for initialize stack
        void push (T val);         // use for push the element in the end of a stack
        void pushmust (T val);     // use for push the element despite the size
        T pop ();                  // use for get element and decrease size
        T top ();                  // use for get element and remain the size
        T mult ();                 // use for multiply two last numbers
        T sum ();                  // use for summarize two numbers
        void print();              // use for print statistic of your stack
        void destroy ();           // use for destroy stack
        int OK ();                 // use for get the status of your stack

    private:
        void Realloc (int Capnew); // program uses it for change the capacity of Data
};


#include "stack.cpp"
