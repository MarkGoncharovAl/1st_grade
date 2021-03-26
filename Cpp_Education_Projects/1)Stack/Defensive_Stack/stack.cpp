template <typename T>
void Stack <T>::newcap (int Capnew)
{
    if (Data == NULL)
    {
        status = NULL_PTR;
        return;
    }

    if (Cap == Capnew)
    {
        status = Warning_useless_function;
        return;
    }

    if (Cap < Capnew)
    {
        char* temp1 = new char[Capnew * sizeof(T) + 2 * sizeof(int)];
        T* temp2 = (T*)(temp1 + sizeof(int));

        for (size_t i = 0; i < Cap; ++i)
            temp2[i] = Data[i];

        delete[] Newmemory;
        Data = temp2;
        Newmemory = temp1;

        Cap = Capnew;

        createkan();
        pushfile << "New Capacity is " << Capnew << "\n";
        return;
    }

    if (Cap > Capnew)
    {
        char* temp1 = new char[Capnew * sizeof(T) + 2 * sizeof(int)];
        T* temp2 = (T*)(temp1 + sizeof(int));

        for (size_t i = 0; i < Capnew; ++i)
            temp2[i] = Data[i];

        delete[] Newmemory;
        Data = temp2;
        Newmemory = temp1;

        Cap = Capnew;

        createkan();
        pushfile << "New Capacity is " << Capnew << "\n";
        return;
    }

    status = NULL_PTR;
    return;
}

template <typename T>
void Stack <T>::push (T val)
{
    if (this == NULL)
    {
        status = EMPTY_STACK;
        return;
    }

    if (Size >= Cap)
    {
        status = FULL_STACK;
        return;
    }

    Data[Size] = val;
    Size++;

    if (!check())
        status = KAN_PROBLEM;
    else
        status = ORDINARY_CASE;

    pushfile << "Pushed " << val << " into " << Size - 1 << std::endl;
    return;
}

template <typename T>
void Stack <T>::pushmust (T val)
{
    if (this == NULL)
    {
        status = EMPTY_STACK;
        return;
    }

    if (Size == Cap)
        newcap (Cap + 1);

    Data[Size] = val;
    Size++;

    pushfile << "Pushed " << val << " into " << Size - 1 << std::endl;
    if (!check())
        status = KAN_PROBLEM;
    else
        status = ORDINARY_CASE;
    return;
}

template <typename T>
T Stack <T>::pop ()
{
    if (this == NULL)
    {
        status = EMPTY_STACK;
        return 0;
    }

    if (Size < 1)
    {
        status = NO_DATA;
        return 0;
    }

    Size--;
    pushfile << "Poped " << Data[Size] << " from " << Size << std::endl;
    if (!check())
        status = KAN_PROBLEM;
    else
        status = ORDINARY_CASE;
    return Data[Size];
}

template <typename T>
T Stack <T>::top ()
{
    if (this == NULL)
    {
        status = EMPTY_STACK;
        return 0;
    }

    if (Size < 1)
    {
        status = NO_DATA;
        return 0;
    }

    pushfile << "Poped " << Data[Size - 1] << " from " << Size << " wihout changing size" << std::endl;
    if (!check())
        status = KAN_PROBLEM;
    else
        status = ORDINARY_CASE;
    return Data[Size - 1];
}

template <typename T>
T Stack <T>::sum ()
{
    if (this == NULL)
    {
        status = EMPTY_STACK;
        return 0;
    }

    if (Size < 2)
    {
        status = NO_DATA;
        return 0;
    }

    Data[Size - 2] = Data[Size - 1] + Data[Size - 2];
    Size -= 1;

    pushfile << "Summed 2 numbers " << Data[Size - 1] << " .Size: " << Size << std::endl;
    if (!check())
        status = KAN_PROBLEM;
    else
        status = ORDINARY_CASE;
    return Data[Size - 1];
}

template <typename T>
T Stack <T>::mult ()
{
    if (this == NULL)
    {
        status = EMPTY_STACK;
        return 0;
    }

    if (Size < 2)
    {
        status = NO_DATA;
        return 0;
    }

    Data[Size - 2] = Data[Size - 1] * Data[Size - 2];
    Size -= 1;

    pushfile << "Multiplied 2 numbers " << Data[Size - 1] << " .Size: " << Size << std::endl;
    if (!check())
        status = KAN_PROBLEM;
    else
        status = ORDINARY_CASE;
    return Data[Size - 1];
}

template <typename T>
void Stack <T>::print()
{
    if (this == NULL)
    {
        status = EMPTY_STACK;
        return;
    }

    if (Size < 0)
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

    if (!check())
        status = KAN_PROBLEM;
    else
        status = ORDINARY_CASE;
    return;
}

template <typename T>
int Stack <T>::OK ()
{
    pushfile << "Programm is checking for mistakes...\n";

    if (status == SMALL_CAP)
    {
        std::cout << "Your capacity is too small!\n";
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
        std::cout << "\nYour stack is full -> Use StackPushMust instead\n";
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
    if (status == KAN_PROBLEM)
    {
        std::cout << "\nKanareyka found mistake of data in the massive\n";
        pushfile << "Mistake " << status << std::endl;
        return 7;
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

    return 1;
}

template <typename T>
void Stack <T>::createkan ()
{
    kancheckstart = (int*)Newmemory;
    kancheckend = (int*)(Data + Cap);

    *kancheckstart = rand() % 10000;
    *kancheckend = rand() % 10000;
    kan_class1 = rand() % 10000;
    kan_class2 = rand() % 10000;

    firstHash = rand() % 10000;
    secondHash = rand() % 10000;

    Hash = firstHash * (*kancheckstart) * kan_class1 + secondHash * (*kancheckend) - kan_class2;
    return;
}

template <typename T>
bool Stack <T>::check ()
{
    if (Hash != (*kancheckend) * secondHash * kan_class1 + firstHash * (*kancheckstart) - kan_class2)
    {
        pushfile << "KAN_PROBLEM\n";
        return false;
    }
    if (status != ORDINARY_CASE)
    {
        pushfile << "STATUS_PROBLEM\n";
        return false;
    }
    return true;
}
