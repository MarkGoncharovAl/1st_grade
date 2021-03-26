#include <iostream>
#include "BMH/BMH.h"

int main()
{
	const std::string base = "123123_456789987654";
	const std::string pattern = "23";
	
	auto result_first = BMH::first_find(base, pattern);
	if (result_first.is_find) {
		std::cout << "Found in place: " << result_first.num_place;
		std::cout << "\nFirst symbol: " << *result_first.place << std::endl;
	}
	else {
		std::cout << "Not found!\n";
	}

	std::cout << "\nNEXT!!!\n\n";

	auto result_count = BMH::count_find(base, pattern);
	if (result_count.is_find) {
		std::cout << "Find " << result_count.count << " times!\n";
	}
	else {
		std::cout << "Not found!\n";
	}

	std::cout << "\nNEXT!!!\n\n";

	auto result_full = BMH::full_find(base, pattern);
	if (result_full.is_find) {
		
		std::cout << "Count: " << result_full.count << std::endl;

		for (const auto& it : result_full.places) {
			std::cout << "Place: " << it.num_place << std::endl;
			std::cout << "First letter: " << *it.iter_place << std::endl;
		}
	}
	else {
		std::cout << "Not found!\n";
	}
	return 0;
}