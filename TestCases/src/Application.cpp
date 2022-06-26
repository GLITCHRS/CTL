#include <iostream>
#include "String/String.h"

int main()
{
	CTL::String name{ "Ahmed Zaki" };
	name.reserve(100);

	std::cout << name << '\n';
	std::cout << name.Length() << '\n';
	std::cout << name.Size() << '\n';
}