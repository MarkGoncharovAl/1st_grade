//!@file main.cpp
//!@mainpage Programm is used for sorting words in the file
//! - main.cpp
//!@author Goncharov Mark Alexandrovich
//!@brief Use for analyse big texts

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>


const int COUNT_SPACES = 20;


long func_count_strings (FILE* fileread, long long* count_char);
void func_read_text (FILE* fileread, char* text, char** point_strings);
int sort_strings (const void* str1, const void* str2);
bool to_up (char* temp);
bool to_down (char* temp);
int sort_strings_rifms (const void* str1, const void* str2);
void print_in_file (FILE* filewrite, char** point_strings, long count_strings);
bool isABC (char temp);
void print_rifms(FILE* filewrite);

/**
    int main()
      ! It's complexity function which just include every other functions!!!!!
    !@param[out] 0 - if work is good
    !@param[out] 1 - if work isn't good
    */

int main()
{
    FILE* fileread = fopen ("In.txt", "r");
    setlocale(LC_ALL, "Russian");

    long long size_file = 0;
    long count_strings = 0;

    if ((count_strings = func_count_strings(fileread, &size_file)) == 0)
    {
        printf ("Your file is empty");
        return 1;
    }

    char* text = (char*) calloc (size_file, sizeof (char));
    char** point_strings = (char**) calloc (count_strings, sizeof (char*));

    func_read_text (fileread, text, point_strings);
    fclose (fileread);


    FILE* filewrite = fopen ("Out.txt", "w");

    qsort(point_strings, count_strings, sizeof(char*), sort_strings);
    print_in_file(filewrite, point_strings, count_strings);

    print_rifms(filewrite);

    qsort(point_strings, count_strings, sizeof(char*), sort_strings_rifms);
    print_in_file(filewrite, point_strings, count_strings);

    fclose (filewrite);
    free (text);
    free (point_strings);
    return 0;
}




/**
    long func_count_strings (FILE* fileread, long long* count_char)
      ! It's counting and it returns count of strings in the file
    !@param[in] fileread is the reading file
    !@param[out] count_char is the number of char symbols
    */

long func_count_strings (FILE* fileread, long long* count_char)
{
    char temp = '0';
    long count_strings = 0;
    *count_char = 0;
    fseek (fileread, 0, 0);
    while ((temp = fgetc (fileread)) != EOF)
    {
        (*count_char)++;
        if (temp == '\n')
            count_strings++;
    }
    return count_strings;
}
/**
    void func_read_text (FILE* fileread, char* text, char** point_strings)
      ! It's reading text and find adress of new line
    !@param[in] fileread is the reading file
    !@param[out] text is the full text
    !@param[out] point_strings is the point to start of new line
    */

void func_read_text (FILE* fileread, char* text, char** point_strings)
{
    fseek (fileread, 0, 0);
    char temp = '\0';

    long long position = 0;
    long count_strings = 1;
    *point_strings = text;
    bool check_word = true;

    while ((temp = fgetc (fileread)) != EOF)
    {
        if (temp == '\n')
        {
            if (check_word)
            {
                *(point_strings + count_strings) = text + position;
                count_strings++;
            }
            text[position] = '\0';
            check_word = true;
        }
        else
        {
            text[position] = temp;
            if (check_word && isABC(temp))
            {
                *(point_strings + count_strings) = text + position;
                count_strings++;
                check_word = false;
            }
        }
        position++;
    }
    text[position] = '\0';
}

/**
    int sort_strings (const void* str1, const void* str2)
      ! It helps us to sort strings fast using qsort
    !@param[in] str1 is the first comparing string
    !@param[in] text is the second comparing string
    */

int sort_strings (const void* str1, const void* str2)
{
    char* a = *(char**)str1;
    char* b = *(char**)str2;
    int len1 = strlen(a);
    int len2 = strlen(b);

    if (len1 == 0)
        return -1;
    if (len2 == 0)
        return 1;

    int i = 0;
    bool bol1 = false;
    bool bol2 = false;
    while (i < len1 && i < len2)
    {
        bol1 = to_down (&a[i]);
        bol2 = to_down (&b[i]);
        if (a[i] < b[i])
        {
            if (bol1)
                to_up (&a[i]);
            if (bol2)
                to_up (&b[i]);
            return -1;
        }
        if (a[i] > b[i])
        {
            if (bol1)
                to_up (&a[i]);
            if (bol2)
                to_up (&b[i]);
            return 1;
        }
        if (bol1)
            to_up (&a[i]);
        if (bol2)
            to_up (&b[i]);
        i++;
    }
    if (i == len1 && i != len2)
        return 1;
    if (i != len1 && i == len2)
        return -1;
    return 0;
}

/**
    void print_in_file (FILE* filewrite, char** point_strings, long count_strings)
      ! It's printing strings after comparing without strings included only notwords
    !@param[in] filewrite is the output file
    !@param[in] point_strings is the point of new line
    !@param[in] count_strings is the count of strings
    */

void print_in_file (FILE* filewrite, char** point_strings, long count_strings)
{
    for (int i = 0; i < count_strings; ++i)
    {
        if (**(point_strings + i) == '\0')
            continue;

        int len = strlen(*(point_strings + i));
        for (int s = 0; s < len; ++s)
            if (*(*(point_strings + i) + s) >= 'a' && *(*(point_strings + i) + s) <= 'z')
            {
                fprintf (filewrite, "%s\n", *(point_strings + i));
                break;
            }
    }
}

/**
    bool isABC (char temp)
      ! It's comparing symbol with the English and Russian letter. It return true or false
    !@param[in] temp is the comparing symbol
    */

bool isABC (char temp)
{
    if ((temp >= 'A' && temp <= 'Z') || (temp >= 'a' && temp <= 'z'))
        return true;
    return false;
}

/**
    int sort_strings_rifms (const void* str1, const void* str2)
      ! It's comparing two strings from the end of the string
    !@param[in] str1 is the first comparing string
    !@param[in] text is the second comparing string
    */

int sort_strings_rifms (const void* str1, const void* str2)
{
    char* a = *(char**)str1;
    char* b = *(char**)str2;

    int len1 = strlen(a);
    int len2 = strlen(b);
    bool bol1 = false;
    bool bol2 = false;

    while (len1 >= 0 && !isABC(a[len1]))
        len1--;
    while (len2 >= 0 && !isABC(b[len2]))
        len2--;

    if (len1 == 0)
        return 1;
    if (len2 == 0)
        return -1;

    while (len1 >= 0 && len2 >= 0)
    {
        bol1 = to_down (&a[len1]);
        bol2 = to_down (&b[len2]);

        if (a[len1] < b[len2])
        {
            if (bol1)
                to_up (&a[len1]);
            if (bol2)
                to_up (&b[len2]);
            return -1;
        }

        if (a[len1] > b[len2])
        {
            if (bol1)
                to_up (&a[len1]);
            if (bol2)
                to_up (&b[len2]);
            return 1;
        }

        if (bol1)
            to_up (&a[len1]);
        if (bol2)
            to_up (&b[len2]);

        len1--;
        len2--;
    }

    if (len1 == 0 && len2 != 0)
        return -1;
    if (len1 != 0 && len2 == 0)
        return 1;

    return 0;
}

/**
    bool to_down (char* temp)
      ! It's translate word to low tab
    !@param[in] temp - a letter that we have to translate
    !@param[out] true - when letter was big
    !@param[out] false - when letter wasn't big
    */

bool to_down (char* temp)
{
    if (isABC(*temp) && *temp < 'a')
    {
        *temp = (char)((int)*temp + (int)('a' - 'A'));
        return true;
    }
    return false;
}

/**
    bool to_up (char* temp)
      ! It's translate word to upper tab
    !@param[in] temp - a letter that we have to translate
    !@param[out] true - when letter was small
    !@param[out] false - when letter wasn't small
    */

bool to_up (char* temp)
{
    if (isABC(*temp) && *temp > 'Z')
    {
        *temp = (char)((int)*temp - (int)('a' - 'A'));
        return true;
    }
    return false;
}

void print_rifms(FILE* filewrite)
{
    for (int i = 0; i < COUNT_SPACES; ++i)
        fputc('\n', filewrite);

    for (int i = 0; i < COUNT_SPACES; ++i)
        fprintf(filewrite, "RIFMS\n");

    for (int i = 0; i < COUNT_SPACES; ++i)
    fputc('\n', filewrite);
}