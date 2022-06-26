#include <iostream>
#include "String/String.h"

int main()
{
	CustomSTL::String name1{ "Ahmed" };

	std::cout << name1[0] << '\n';
	std::cout << name1[name1.Length() - 1] << '\n';
	std::cout << sizeof(CustomSTL::String) << '\n';
}