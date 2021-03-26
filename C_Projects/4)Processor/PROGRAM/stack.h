#include <iostream>
#include <fstream>

const char ORDINARY_CASE = '0';
const char Warning_useless_function = 'A';
const char Warning_small_size = 'B';
const char SMALL_CAP = 'a';
const char EMPTY_STACK = 'b';
const char FULL_STACK = 'c';
const char NO_DATA = 'd';
const char MEMORY_PROBLEM = 'e';
const char NULL_PTR = 'f';

class Stack
{
    public: int64_t *Data;

    public: int64_t ax;
    public: int64_t bx;
    public: int64_t cx;
    public: int64_t dx;

    public: size_t Size;
    public: size_t Cap;
    public: char status;

    public:
        void init (int Capacity); 
        void push (int64_t val); 
        void pushmust (int64_t val);  
        int64_t pop ();               
        int64_t top ();               
        int64_t mult ();                
        int64_t sum ();                  
        int64_t sub ();
        int64_t div ();
        void print();              
        void destroy ();          
        int OK ();                

    private:
        void Realloc (size_t Capnew);
};


#include "stack.cpp"
