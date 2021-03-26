#include <iostream>
#include "Array2D.h"

int main()
{
	lib::Array2D<int> arr1(5, 6); //new int[5][6]
	
	int mas[20] = {};
	lib::Array2D<int> arr2(mas, 4, 5); //now data copied to the array2D

	lib::Array2D<char> arr3(2, 2);
	for (char& elem : arr3)
		elem = 3;
	//the same is below
	//auto == lib::Array2D<char>::iterator
	for (auto iter = arr3.begin(); iter != arr3.end(); ++iter) {
		*iter = '3';
	}

	std::cout << arr3[1][0]; // the same as ordinary array

}