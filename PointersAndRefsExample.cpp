#include <iostream>

int val1 = 1;
int val2 = 2;
int* valPtr = &val1;
int& valRef = val1;

void printVals()
{
	std::cout << "Values:" << std::endl;
	std::cout << "val1: " << val1 << " val2: " << val2 << " valPtr: " << *valPtr << " valRef: " << valRef;
	std::cout << std::endl;
}

int main()
{
	printVals();
	return 0;
}