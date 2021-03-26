#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>

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
const char KAN_PROBLEM = 'g';

template <typename T>
class Stack
{
    private: int kan_class1;
    private: char* Newmemory;
    private: T *Data;
    private: size_t Size;
    private: size_t Cap;

    private: int* kancheckstart;
    private: int* kancheckend;
    private: long long Hash;
    private: int firstHash;
    private: int secondHash;

    public: char status;
    public:
        void newcap (int Capnew);  // program uses it for change the capacity of Data
        void push (T val);         // use for push the element in the end of a stack
        void pushmust (T val);     // use for push the element despite the size
        T pop ();                  // use for get element and decrease size
        T top ();                  // use for get element and remain the size
        T mult ();                 // use for multiply two last numbers
        T sum ();                  // use for summarize two numbers
        void print();              // use for print statistic of your stack
        void destroy ();           // use for destroy stack
        int OK ();                 // use for get the status of your stack

    private: bool check ();
    private: void createkan ();
    private: int kan_class2;

    public:Stack()
    {
        Cap = 1001;
        Newmemory = new char[Cap * sizeof(T) + 2 * sizeof (int)];
        Data = (T*) (Newmemory + sizeof (int));
        Size = 0;

        srand (time (NULL));

        kancheckstart = (int*)Newmemory;
        kancheckend = (int*)(Data + Cap);

        *kancheckstart = rand() % 10000;
        *kancheckend = rand() % 10000;
        kan_class1 = rand() % 10000;
        kan_class2 = rand() % 10000;

        firstHash = rand() % 10000;
        secondHash = rand() % 10000;

        Hash = firstHash * (*kancheckstart) * kan_class1 + secondHash * (*kancheckend) - kan_class2;

        pushfile << "Stack was created" << std::endl;
        status = ORDINARY_CASE;
        return;
    }

    public:~Stack()
    {
        Cap = 0;
        Size = 0;
        *kancheckend = -1;
        *kancheckstart = -1;
        kan_class1 = -1;
        kan_class2 = -1;
        Hash = -2;

        pushfile << "Stack was destroyed" << std::endl;
        status = ORDINARY_CASE;
    }
};

#include "stack.cpp"
