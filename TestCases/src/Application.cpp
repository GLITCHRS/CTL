#include <iostream>
#include "String/String.h"

int main()
{
	CustomSTL::String name1{ "Ahmed" };

	std::cout << (name1 > "Ahme") << '\n';
	std::cout << (name1 != "Ahmed") << '\n';
	std::cout << (CustomSTL::String{ "Ahmeda" } != "Ahmed") << '\n';
}