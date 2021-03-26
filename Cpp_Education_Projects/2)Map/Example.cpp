#include <iostream>
#include <string>
#include "Map.h"

void add (std::string *new_string)
{
    *new_string += "_added";
}

void print (std::string *new_string)
{
    std::cout << "Next: " << *new_string << "\t";
}

int main()
{
    Map <std::string, std::string> my_map;

    my_map.insert("g", "g");
    my_map.insert("f", "f");
    my_map.insert("c", "c");
    my_map.insert("d", "d");
    my_map.insert("e", "e");
    my_map.insert("b", "b");
    my_map.insert("a", "a");
    my_map.insert("h", "h");
    my_map.insert("j", "j");
    my_map.insert("i", "i");
    my_map.insert("k", "k");
    my_map.insert("o", "o");
    my_map.insert("n", "n");
    my_map.insert("l", "l");
    my_map.insert("m", "m");

    if (!my_map.erase("gf")) {
        std::cout << "\n404: NOT FOUND\n";
    }

    if (!my_map.erase("c")) {
        std::cout << "\n404: NOT FOUND\n";
    }
    else
        my_map.full_print();




    std::cout << "\n\n\n\nANOTHER PROGRAMM:\n\n\n\n";



    Map <int, std::string> MyMap;
    MyMap.insert (6, "mother");
    MyMap.insert (65, "father");

    Pair <int, std::string> Pair1;
    Pair1.make_pair(43, "PAIR");
    MyMap.insert(Pair1);

    MyMap.print(43);
    MyMap.print (1090);
    MyMap.print(6);

    std::cout << "\nNext tests:\n\n\n";

    std::string findings;
    bool check = MyMap.find(5, &findings);
    if (check)
        std::cout << "FOUND: " << findings << std::endl;
    else
        std::cout << "I didn't find this\n";

    check = MyMap.find(43, &findings);
    if (check)
        std::cout << "FOUND: " << findings << std::endl;
    else
        std::cout << "I didn't find this\n";


    std::cout << "\nNext tests:\n\n\n";
    MyMap.full_print ();


    std::cout << "\nNext tests:\n\n\n";
    MyMap.foreach (print);
    MyMap.foreach (add);
    std::cout << "\n\n";
    MyMap.full_print ();

    return 0;
}
