#include <iostream>
#include "String/String.h"

int main()
{
	std::string te{ "Test!" };
	CustomSTL::String a{ te };
	CustomSTL::String b{ " World!" };

	std::cout << (a + b) << '\n';
}