#include <iostream>
#include <fstream>
#include <cassert>
#include "Tree.h"
#define _CRT_SECURE_NO_WARNINGS

int main()
{
	std::ifstream input_file("expression.txt");
	if (!input_file.is_open()) {
		printf("Problems with file\n");
		assert(0);
	}


	std::string file_string;
	input_file >> file_string;
	std::cout << file_string << std::endl;

	Tree main_tree;
	main_tree.read_string_to_Tree(&(file_string[0]));


	double variables[COUNT_VALUE] = {};
	for (int i = 0; i < COUNT_VALUE; ++i) {
		printf("Enter your x%d: ", i + 1);
		scanf_s("%lf", variables + i);
	}


	printf("\nYour Tree has a form: ");
	main_tree.print();
	printf("\nThe result: %.3lf\n\n", main_tree(variables));

	Tree dif_tree;
	dif_tree.dif(main_tree);
	printf("Your differential Tree has a form: ");
	dif_tree.print();
	printf("\nThe result of differential: %.3lf\n\n", dif_tree(variables));


	Tree dif_dif_tree;
	dif_dif_tree.dif(dif_tree);
	printf("Your differential Tree of differential Tree has a form: ");
	dif_dif_tree.print();
	printf("\nThe result of differential of differential: %.3lf\n", dif_dif_tree(variables));
	

	
	input_file.close();
	return 0;
}