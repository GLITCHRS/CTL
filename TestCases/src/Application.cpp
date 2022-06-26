#include <iostream>
#include "String/String.h"

int main()
{
	CTL::String name1{"Ahmed"};

	std::cout << name1[0] << '\n';
	std::cout << name1[name1.Length() - 1] << '\n';
	std::cout << sizeof(CTL::String) << '\n';
}