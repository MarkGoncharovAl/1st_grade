#include "stack.h"
#include <iostream>

int main()
{
    Stack <int> data;
    data.init (6);
    for (int i = 0; i < 10; ++i)
    {
        data.pushmust (i);
        data.OK();
    }

    for (int i = 0; i < 5; ++i)
        std::cout << data.pop() << std::endl;

    printf("Sum is %d\n", data.sum());
    data.print();
    data.destroy();
    return 0;
}
