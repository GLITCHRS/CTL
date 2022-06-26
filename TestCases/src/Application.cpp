#include <iostream>
#include "String/String.h"

int main()
{
	CustomSTL::String name1{ "Ahmed" };

	std::cout << (name1 >= "Ahmeda") << '\n';
}