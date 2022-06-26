#include <iostream>
#include "String/String.h"

int main()
{
	CustomSTL::String name1{ "Ahmed" };
	CustomSTL::String to_compare{ "Ahmed" };

	std::cout << (name1 == to_compare) << '\n';
	std::cout << (name1 == "Ahmed") << '\n';
	std::cout << (name1 == std::string{"Ahmed"}) << '\n';
}