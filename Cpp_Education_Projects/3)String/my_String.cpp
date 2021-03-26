#include <iostream>
#include "my_String.h"


int main()
{
	std::cout << "//COPY = slowly\n\n";
	STR(String1);
	STR(String2);
	
	String String3 = String1 + String2;
	String3.dump();

	std::cout << "\nNEXT TESTS\n\n";

	String String4 = std::move(String1) + String2;
	String4.dump();
	STR(String0); //обратно, ведь move мог уничтожить (а точнее реально уничтожил) String1

	std::cout << "\nNEXT TESTS\n\n";

	std::string Std_string = "Std_string";
	String4 = String0 + Std_string + String2 + "Const_char_string";
	//но вот после этого момента String0 - уничтожен
	std::cout << std::endl;
	String4.dump();
	std::cout << std::endl;


	return 0;
}
