#include <iostream>
#include "String/String.h"

int main()
{
	CustomSTL::String name1{ "Ahmed" };

	std::cout << name1[0] << '\n';
	std::cout << name1[name1.Count() - 2] << '\n';
}