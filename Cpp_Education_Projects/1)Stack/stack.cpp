template <typename T>
void Stack <T>::Realloc (int Capnew)
{
    if (status != ORDINARY_CASE)
    {
        std::cout << "\nREALLOC DIDNOT WORK\n";
        return;
    }

    if (Cap == Capnew)
    {
        status = Warning_useless_function;
        return;
    }

    if (Cap < Capnew)
    {
        T* strcop = new T[Capnew];

        for (int i = 0; i < Cap; ++i)
            strcop[i] = Data[i];

        delete[] Data;
        Data = strcop;
        status = ORDINARY_CASE;
        return;
    }

    if (Cap > Capnew)
    {
        T* strcop = new T[Capnew];

        for (int i = 0; i < Capnew; ++i)
            strcop[i] = Data[i];

        delete[] Data;
        Data = strcop;
        status = ORDINARY_CASE;
        return;
    }

    status = NULL;
    return;
}

template <typename T>
void Stack <T>::init (int Capacity)
{
    if (Capacity <= 0)
    {
        status = SMALL_CAP;
        return;
    }

    Size = 0;
    Cap = Capacity;
    Data = new T[Cap];

    pushfile << "Stack was created" << std::endl;
    status = ORDINARY_CASE;
    return;
}

template <typename T>
void Stack <T>::push (T val)
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

    pushfile << "Pushed " << val << " into " << Size - 1 << std::endl;
    status = ORDINARY_CASE;
    return;
}

template <typename T>
void Stack <T>::pushmust (T val)
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

    pushfile << "Pushed " << val << " into " << Size - 1 << std::endl;
    status = ORDINARY_CASE;
    return;
}

template <typename T>
T Stack <T>::pop ()
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
    pushfile << "Poped " << Data[Size] << " from " << Size << std::endl;
    status = ORDINARY_CASE;
    return Data[Size];
}

template <typename T>
T Stack <T>::top ()
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

    pushfile << "Poped " << Data[Size - 1] << " from " << Size << " wihout changing size" << std::endl;
    status = ORDINARY_CASE;
    return Data[Size - 1];
}

template <typename T>
T Stack <T>::sum ()
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

    Data[Size - 2] = Data[Size - 1] + Data[Size - 2];
    Size--;

    pushfile << "Summed 2 numbers " << Data[Size - 1] << " .Size: " << Size << std::endl;
    status = ORDINARY_CASE;
    return Data[Size - 1];
}

template <typename T>
T Stack <T>::mult ()
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

    pushfile << "Multiplied 2 numbers " << Data[Size - 1] << " .Size: " << Size << std::endl;
    status = ORDINARY_CASE;
    return Data[Size - 1];
}

template <typename T>
void Stack <T>::print()
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

    pushfile << "Printing Stack:\nStatus: " << status << std::endl;
    pushfile << "Size: " << Size << "\nCapacity: " << Cap << std::endl;
    for (size_t i = 0; i < Size; ++i)
        pushfile << "[" << i << "/" << Size - 1 << "]: " << Data[i] << std::endl;

    status = ORDINARY_CASE;
    return;
}

template <typename T>
void Stack <T>::destroy ()
{
    if (status != ORDINARY_CASE)
    {
        std::cout << "DESTROY DIDNOT WORK\n";
        return;
    }

    delete[] Data;
    Cap = 0;

    pushfile << "Stack was destroyed" << std::endl;
    status = ORDINARY_CASE;
    return;
}

template <typename T>
int Stack <T>::OK ()
{
    if (status == SMALL_CAP)
    {
        std::cout << "\nYour capacity is too small!\n";
        pushfile << "Mistake " << status << std::endl;
        return 1;
    }
    if (status == EMPTY_STACK)
    {
        std::cout << "\nYour stack wasn't created\n";
        pushfile << "Mistake " << status << std::endl;
        return 2;
    }
    if (status == FULL_STACK)
    {
        std::cout << "\nYour stack is full -> Use (array).pushmust() instead\n";
        pushfile << "Mistake " << status << std::endl;
        return 3;
    }
    if (status == NO_DATA)
    {
        std::cout << "\nYour data is empty\n";
        pushfile << "Mistake " << status << std::endl;
        return 4;
    }
    if (status == MEMORY_PROBLEM)
    {
        std::cout << "\nMemory maybe was overload in the disk\n";
        pushfile << "Mistake " << status << std::endl;
        return 5;
    }
    if (status == NULL_PTR)
    {
        std::cout << "\nPushmust function can't be used - Data memory is null\n";
        pushfile << "Mistake " << status << std::endl;
        return 6;
    }
    if (status == Warning_useless_function)
    {
        std::cout << "\nUsing function is useless\n";
        pushfile << "Warning " << status << std::endl;
        return 0;
    }
    if (status == Warning_small_size)
    {
        std::cout << "\nSize is too small for function work\n";
        pushfile << "Warning " << status << std::endl;
        return 0;
    }
    if (status == ORDINARY_CASE)
        return 0;
}
