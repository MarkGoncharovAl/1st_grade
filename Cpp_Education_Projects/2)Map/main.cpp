#include <iostream>
#include <iterator>
#include <vector>
#include "Map.h"


int main()
{
    Map <std::string, std::string> my_map;
    my_map("a") = "A";
    my_map("t") = "T";
    my_map("z") = "Z";

    for (auto it = my_map.begin(); it != my_map.end(); ++it) {
        std::cout << *it << std::endl;
    }

    for (auto it = my_map.begin(); it != my_map.end(); ++it) {
        *it += "---------";
    }

    my_map.full_print();


    my_map.erase("a");
    for (auto it = my_map.begin(); it != my_map.end(); ++it) {
        std::cout << *it << std::endl;
    }


    return 0;
}
