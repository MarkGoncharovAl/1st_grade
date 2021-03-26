#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

typedef int CompFunc(const void* a, const void* b);

int Qsort (void* arr, size_t size_of_el, int num, CompFunc* compar);
int comp (const void* a, const void* b);
int Swap (int* arr, int i, int j);

int main()
{
    printf("Put the size of your massive: ");

    int num = 0;
    scanf("%d", &num);
    int* arr = (int*)calloc(num, sizeof(int));

    for (int i = 0; i < num; ++i)
        scanf ("%d", (arr + i));

    if (!Qsort((void*)arr, sizeof(int), num, comp))
    {
        printf("\nMistake was found!\n");
        return 1;
    }

    printf ("\nYour sorting massive:\n");
    for (int i = 0; i < num; ++i)
        printf("%d ", arr[i]);

    free (arr);
    return 0;
}

int Qsort (void* arr, size_t size_of_el, int num, CompFunc* compar)
{
    if (arr == NULL)
        return 0;

    if (num < 2)
        return 1;

    srand (time (NULL));
    int Idivide = rand() % num;

    int i = 0;
    int j = num - 1;

    while (i < j)
    {
        while (compar((const void*)(arr + size_of_el * i), (const void*)(arr + size_of_el * Idivide)) < 0)
            ++i;
        while (compar((const void*)(arr + size_of_el * j), (const void*)(arr + size_of_el * Idivide)) > 0)
            --j;

        if (i <= j)
        {
            if (i == Idivide)
                Idivide = i;
            if (j == Idivide)
                Idivide = j;

            if (!Swap (&i, &j))
                return 0;
            ++i;
            --j;
        }
    }

    Qsort (arr + size_of_el * i, size_of_el, num - i, compar);
    Qsort (arr, size_of_el, j + 1, compar);

    return 1;
}

int comp (const void* a, const void* b)
{
    return (*((const int*)a) - *((const int*)b));
}

int Swap (int* num1, int* num2)
{
    if (!num1 || !num2)
        return 0;
    
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
    
    retrun 1;
}