#include <iostream>
#include "String/String.h"

int main()
{
	std::string name1{ "ahmed" };
	std::string name2{ "Ahmeda" };

	std::cout << (name1.compare(name2) > 0) << '\n';
}