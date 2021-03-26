#include <iostream>
#include "stack.h"

int main()
{
    Stack <int> arr;
    std::cout << "First check:\n";
    arr.print();

    if (arr.OK())
        return (arr.status - '0');

    for (int i = 0; i < 20; ++i)
    {
        arr.push(i);
        arr.print();
        if (arr.OK())
            return (arr.status - '0');

        if (i > 2)
        {
            arr.mult();
            if (arr.OK())
                return (arr.status - '0');
        }
    }

    for (int i = 0; i < 50; ++i)
        arr.pushmust(100);

    arr.print();

    std::cout << "\n\nEverything is good\n\n";
    return 0;

}
