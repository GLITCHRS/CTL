#include <iostream>
#include <string>

#include "String/String.h"

int main()
{
	CTL::Dynamic::String a{ "Hi" };

	a.Reserve(10);

	std::cout << a << '\n';
	std::cout << a.Length() << '\n';
	std::cout << a.Size() << '\n';

	a *= 1;

	std::cout << a << '\n';
	std::cout << a.Length() << '\n';
	std::cout << a.Size() << '\n';
}