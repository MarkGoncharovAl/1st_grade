#include <iostream>
#include "span.h"

int main()
{
	//don't afraid constexp - it's almost equal to const (or look at cpp.ref)
	constexpr std::size_t len = 9;
	int mas[len] = {};
	lib::span<int> new_span(mas, 9);

	//Now, we've got an array, how can we initialize it??
	//1
	for (std::size_t i = 0; i < len; ++i) {
		*(new_span + i) = i;
	}

	//2
	std::size_t i = 0;
	while (!new_span.is_end()) {
		new_span[0] = i;
		new_span++;
		i++;
	}
	new_span.to_begin(); //return iterator to start position

	//3
	i = 0;
	while (i < len) {
		new_span[i] = i;
		i++;
	}
	
	//4 - the best
	new_span.each([]
		(int& cur_int, std::size_t cur_number) 
		{cur_int = cur_number; });
	//The last variant is so string, you can even don't use second parametr
	
	//5
	i = 0;
	new_span.each([&i]
		(int& cur_int)
		{cur_int = i; i++; });
	//It's safe and fast opportunity to do this
	//std::bind and pointers to ordinary function can work too
	//So you can realize everything that you want using lambda-functions!!!)


	//for reading you can use even more safe opportunities - const_span<T> can be used too or...
	//The best variant to print out - const T&
	new_span.each([]
		(const int& cur_int) 
		{std::cout << cur_int << std::endl; });

	//of course there are many other opportunities - check Github or read span.h)
}