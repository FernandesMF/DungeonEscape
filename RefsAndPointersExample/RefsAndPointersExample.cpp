// This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>


int val1 = 1;
int val2 = 2;
int* valPtr = &val1;
int& valRef = val1;

void printVals()
{
	std::cout << std::endl;
	std::cout << "Values:" << std::endl << "        ";
	std::cout << "val1: " << val1 << " val2: " << val2 << " valPtr: " << *valPtr << " valRef: " << valRef;
	std::cout << std::endl;
	std::cout << "Addresses:" << std::endl << "        ";
	std::cout << "val1: " << &val1 << " val2: " << &val2 << " valPtr: " <<valPtr << " valRef: " << &valRef;
	std::cout << std::endl;
}

int main()
{
	printVals();

	std::cout << std::endl << "Now let's mess with those values." << std::endl;
	std::cout << "Repointing the pointer:" << std::endl;
	valPtr = &val2;
	printVals();

	std::cout << std::endl;
	std::cout << "Rewriting value at pointer:" << std::endl;
	*valPtr = *valPtr+1;
	printVals();

	std::cout << std::endl;
	std::cout << "Rewriting value at reference:" << std::endl;
	valRef = valRef + 1;
	printVals();

	return 0;
}