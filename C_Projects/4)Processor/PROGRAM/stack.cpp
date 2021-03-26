void Stack::Realloc (size_t Capnew)
{
    if (Cap < Capnew)
    {
        int64_t* strcop = new int64_t[Capnew];

        for (size_t i = 0; i < Cap; ++i)
            strcop[i] = Data[i];

        delete[] Data;
        Data = strcop;
        status = ORDINARY_CASE;
        return;
    }

    if (Cap > Capnew)
    {
        int64_t* strcop = new int64_t[Capnew];

        for (size_t i = 0; i < Capnew; ++i)
            strcop[i] = Data[i];

        delete[] Data;
        Data = strcop;
        status = ORDINARY_CASE;
        return;
    }

    status = NULL_PTR;
    return;
}

void Stack::init (int Capacity)
{
    Size = 0;
    Cap = Capacity;
    Data = new int64_t[Cap];

    status = ORDINARY_CASE;
    return;
}

void Stack::push (int64_t val)
{
    if (status != ORDINARY_CASE)
    {
        std::cout << "PUSH DIDNOT WORK\n";
        return;
    }

    if (Size >= Cap)
    {
        status = FULL_STACK;
        return;
    }

    Data[Size] = val;
    Size++;

    return;
}

void Stack::pushmust (int64_t val)
{
    if (status != ORDINARY_CASE)
    {
        std::cout << "PUSHMUST DIDNOT WORK\n";
        return;
    }

    if (Size == Cap)
    {
        Realloc (Cap + 1);
        if (Data == NULL)
        {
            status = MEMORY_PROBLEM;
            return;
        }
        Cap++;
    }

    Data[Size] = val;
    Size++;

    return;
}

int64_t Stack::pop ()
{
    if (status != ORDINARY_CASE)
    {
        std::cout << "POP DIDNOT WORK\n";
        return Data[0];
    }

    if (Size == 0)
    {
        status = NO_DATA;
        return 0;
    }

    Size--;

    return Data[Size];
}

int64_t Stack::top ()
{
    if (status != ORDINARY_CASE)
    {
        std::cout << "TOP DIDNOT WORK\n";
        return Data[0];
    }

    if (Size == 0)
    {
        status = NO_DATA;
        return 0;
    }

    return Data[Size - 1];
}

int64_t Stack::sum ()
{
    if (status != ORDINARY_CASE)
    {
        std::cout << "SUM DIDNOT WORK\n";
        return -1;
    }

    if (Size <= 1)
    {
        status = NO_DATA;
        return -2;
    }

    Data[Size - 2] = Data[Size - 1] + Data[Size - 2];
    Size--;

    return Data[Size - 1];
}

int64_t Stack::sub ()
{
    if (status != ORDINARY_CASE)
    {
        std::cout << "SUM DIDNOT WORK\n";
        return -1;
    }

    if (Size <= 1)
    {
        status = NO_DATA;
        return 0;
    }

    Data[Size - 2] = Data[Size - 2] - Data[Size - 1];
    Size--;

    return Data[Size - 1];
}

int64_t Stack::mult ()
{
    if (status != ORDINARY_CASE)
    {
        std::cout << "MULT DIDNOT WORK\n";
        return 0;
    }

    if (Size <= 1)
    {
        status = NO_DATA;
        return 0;
    }

    Data[Size - 2] = Data[Size - 1] * Data[Size - 2];
    Size--;

    return Data[Size - 1];
}

int64_t Stack::div ()
{
    if (status != ORDINARY_CASE)
    {
        std::cout << "SUM DIDNOT WORK\n";
        return -1;
    }

    if (Size <= 1)
    {
        status = NO_DATA;
        return 0;
    }

    Data[Size - 2] = Data[Size - 2] / Data[Size - 1];
    Size--;

    return Data[Size - 1];
}

void Stack::print()
{
    if (Size <= 0)
    {
        status = Warning_small_size;
        return;
    }

    std::cout << "Printing Stack:\nStatus: " << status << std::endl;
    std::cout << "Size: " << Size << "\nCapacity: " << Cap << std::endl;
    for (size_t i = 0; i < Size; ++i)
        std::cout << "[" << i << "/" << Size - 1 << "]: " << Data[i] << std::endl;

    status = ORDINARY_CASE;
    return;
}

void Stack::destroy ()
{
    if (status != ORDINARY_CASE)
    {
        std::cout << "DESTROY DIDNOT WORK\n";
        return;
    }

    delete[] Data;
    Cap = 0;

    return;
}

int Stack::OK ()
{
    if (status == SMALL_CAP)
    {
        std::cout << "\n!!Your capacity is too small!\n\n\n";
        return 1;
    }
    if (status == EMPTY_STACK)
    {
        std::cout << "\n!!Your stack wasn't created\n\n\n";
        return 2;
    }
    if (status == FULL_STACK)
    {
        std::cout << "\n!!Your stack is full -> Use (array).pushmust() instead\n\n\n";
        return 3;
    }
    if (status == NO_DATA)
    {
        std::cout << "\n!!You haven't necessary data to start operation\n\n\n";
        return 4;
    }
    if (status == MEMORY_PROBLEM)
    {
        std::cout << "\n!!Memory maybe was overload in the disk\n\n\n";
        return 5;
    }
    if (status == NULL_PTR)
    {
        std::cout << "\n!!Pushmust function can't be used - Data memory is null\n\n\n";
        return 6;
    }
    if (status == Warning_useless_function)
    {
        std::cout << "\n!!Using function is useless\n\n\n";
        return 0;
    }
    if (status == Warning_small_size)
    {
        std::cout << "\n!!Size is too small for function work\n\n\n";
        return 0;
    }
    if (status == ORDINARY_CASE)
        return 0;

    return 4;
}
