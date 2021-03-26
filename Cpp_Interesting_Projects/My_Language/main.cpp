#include <iostream>
#include <fstream>
#include <memory>
#include "Parsing/Parsing.h"

//in order to use on GCC fopen
#if (!defined (_TRUNCATE) || defined (__CYGWIN__) || defined (_MEMORY_S_DEFINED)) 
    #define  fopen_s(file, name, mode)  ( *(file) = fopen ((name), (mode)) ) 
#endif


std::string ReadFile(const char* location);

int main()
{
    std::string text_programm = ReadFile("Example_of_using/prog.txt");

    Programm new_Parsing(std::move(text_programm));
    const double result = new_Parsing.Start();

    std::cout << "Final result is " << result << std::endl;
    return 0;
}


//just copied from old code
std::string ReadFile(const char* location)
{
    std::ifstream file;     file.open(location, std::ios_base::in);
    std::string file_string;

    char temp = '0';
    for (file.get(temp); !file.eof(); file.get(temp)) {
        file_string.push_back(temp);
    }

    return std::move(file_string);
}