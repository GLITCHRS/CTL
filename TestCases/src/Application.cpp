#include <iostream>
#include "String/String.h"

int main()
{
	CTL::String name{ 100 };
	name.append("Ahmed Zaki");

	std::cout << name << '\n';
	std::cout << name.Length() << '\n';
	std::cout << name.Size() << '\n';
}